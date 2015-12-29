#include "Aircraft.h"
#include "ResourceHolder.h"
#include "CommandQueue.h"
#include "Data.h"
#include "Math.h"
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

namespace
{
	const std::vector<AircraftData> Table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
	:Entity(Table[type].hitpoints)
	,type(type)
	,fire_command()
	,missile_command()
	,fire_countdown(sf::Time::Zero)
	,is_firing(false)
	,is_missile_launch(false)
	,sprite(textures.get(Table[type].texture))
	,fire_rate(1)
	,spread_level(1)
	,missile_ammo(10)
	,show_explosion(true)
	,spawned_pickup(false)
	,pickup_command()
	,travalled_distance(0.f)
	,direction_index(0)
	,missile_display(nullptr)
	,health_display(nullptr)
	,explosion(textures.get(Textures::Explosion))
{
	explosion.setFrameSize(sf::Vector2i(256, 256));
	explosion.setNumFrames(16);
	explosion.setScale(1.1f, 1.1f);
	explosion.setDuration(sf::seconds(1.2f));
	explosion.setPosition(0.f, -100.f);

	explosion.setOrigin(explosion.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	fire_command.category = Category::SceneAirLayer;
	fire_command.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createBullets(node, textures);
	};

	missile_command.category = Category::SceneAirLayer;
	missile_command.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
	};

	pickup_command.category = Category::SceneAirLayer;
	pickup_command.action   = [this, &textures] (SceneNode& node, sf::Time)
	{
		createPickup(node, textures);
	};


	if (getCategory() == Category::PlayerAircraft)
	{
		std::unique_ptr<TextNode> health(new TextNode(fonts, ""));
		health_display = health.get();
		attachChild(std::move(health));

		std::unique_ptr<TextNode> missile(new TextNode(fonts, ""));
		missile->setPosition(0, 70);
		missile_display = missile.get();
		attachChild(std::move(missile));
	}

	updateTexts();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	if (isDestroyed() && show_explosion)
		target.draw(explosion, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isDestroyed())
	{
		checkPickupDrop(commands);
		explosion.update(dt);
		return;
	}

	checkProjectileLaunch(dt, commands);

	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	updateTexts();
}

unsigned int Aircraft::getCategory() const
{
	if (isAllied())
		return Category::PlayerAircraft;
	else
		return Category::EnemyAircraft;
}

sf::FloatRect Aircraft::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

bool Aircraft::isMarkedForRemoval() const
{
	return isDestroyed() && (explosion.isFinished() || !show_explosion);
}

void Aircraft::remove()
{
	Entity::remove();
	show_explosion = false;
}

bool Aircraft::isAllied() const
{
	return type == Eagle;
}

float Aircraft::getMaxSpeed() const
{
	return Table[type].speed;
}

void Aircraft::increaseFireRate()
{
	if (fire_rate < 10)
		++fire_rate;
}

void Aircraft::increaseSpread()
{
	if (spread_level < 3)
		++spread_level;
}

void Aircraft::collectMissiles(unsigned int count)
{
	missile_ammo += count;
}

void Aircraft::fire()
{
	if (Table[type].fireInterval != sf::Time::Zero)
		is_firing = true;
}

void Aircraft::launchMissile()
{
	if (missile_ammo > 0)
	{
		is_missile_launch = true;
		--missile_ammo;
	}
}

void Aircraft::updateMovementPattern(sf::Time dt)
{
	const std::vector<Direction>& directions = Table[type].directions;
	if (!directions.empty())
	{
		if (travalled_distance > directions[direction_index].distance)
		{
			direction_index = (direction_index + 1) % directions.size();
			travalled_distance = 0.f;
		}
		setVelocity(Math::cartesian(getMaxSpeed(), directions[direction_index].angle));
		travalled_distance += getMaxSpeed() * dt.asSeconds();
	}
}

void Aircraft::checkPickupDrop(CommandQueue& commands)
{
	if (!isAllied() && Math::random(3) == 0 && !spawned_pickup)
		commands.push(pickup_command);
	spawned_pickup = true;
}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
	if (!isAllied())
		fire();

	if (is_firing && fire_countdown <= sf::Time::Zero)
	{
		commands.push(fire_command);
		fire_countdown += Table[type].fireInterval / (fire_rate + 1.f);
		is_firing = false;
	}
	else if (fire_countdown > sf::Time::Zero)
	{
		fire_countdown -= dt;
		is_firing = false;
	}

	if (is_missile_launch)
	{
		commands.push(missile_command);
		is_missile_launch = false;
	}
}

void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures) const
{
	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;
	
	if (isAllied())
	{
		switch (spread_level)
		{
		case 1:
			createProjectile(node, type, 0.0f, 0.5f, textures);
			break;

		case 2:
			createProjectile(node, type, -0.33f, 0.33f, textures);
			createProjectile(node, type, +0.33f, 0.33f, textures);
			break;

		case 3:
			createProjectile(node, type, -0.5f, 0.33f, textures);
			createProjectile(node, type, 0.0f, 0.5f, textures);
			createProjectile(node, type, +0.5f, 0.33f, textures);
			break;
		}
	}
	else
	{
		if (Aircraft::type == Aircraft::Raptor)
		{
			createProjectile(node, type, -0.99f, 0.33f, textures);
			createProjectile(node, type, -0.66f, 0.5f, textures);
			createProjectile(node, type, +0.99f, 0.5f, textures);
			createProjectile(node, type, +0.66f, 0.33f, textures);
		}
		else if (Aircraft::type == Aircraft::Boss)
		{
			createProjectile(node, type, -0.99f, 0.22f, textures);
			createProjectile(node, type, -0.66f, 0.33f, textures);
			createProjectile(node, type, -0.33f, 0.5f, textures);
			createProjectile(node, type, +0.33f, 0.5f, textures);
			createProjectile(node, type, +0.99f, 0.33f, textures);
			createProjectile(node, type, +0.66f, 0.22f, textures);
		}
		else if (Aircraft::type == Aircraft::Avenger)
		{
			createProjectile(node, type, 0.0f, 0.5f, textures);
		}
	}
}

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * sprite.getGlobalBounds().width, yOffset * sprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectile->getMaxSpeed());
	if (!isAllied())
	{
		projectile->setRotation(180.f);
	}
	projectile->setPosition(getWorldPosition() + offset * Math::sign(isAllied()));
	projectile->setVelocity(velocity * Math::sign(isAllied()));
	node.attachChild(std::move(projectile));
}

void Aircraft::updateTexts()
{
	if (health_display)
	{
		health_display->setString(std::to_string(getHitpoints()) + " HP");
		health_display->setPosition(0.f, 50.f);
		health_display->setRotation(-getRotation());
	}

	if (missile_display)
	{
		if (missile_ammo == 0)
			missile_display->setString("");
		else
			missile_display->setString("M: " + std::to_string(missile_ammo));
	}
}

void Aircraft::createPickup(SceneNode& node, const TextureHolder& textures) const
{
	auto type = static_cast<Pickup::Type>(Math::random(Pickup::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}