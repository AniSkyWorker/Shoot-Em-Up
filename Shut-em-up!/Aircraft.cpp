#include "Aircraft.h"
#include "ResourceHolder.h"
#include "CommandQueue.h"
#include "Data.h"
#include "Math.h"
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include "EmitterNode.h"


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
	,missile_countdown(sf::Time::Zero)
	,is_firing(false)
	,is_missile_launch(false)
	,sprite(textures.get(Table[type].texture), Table[type].texture_rect)
	,fire_rate(0)
	,spread_level(1)
	,missile_ammo(10)
	,show_explosion(true)
	,spawned_pickup(false)
	,pickup_command()
	,travalled_distance(0.f)
	,direction_index(0)
	,missile_display(nullptr)
	,missile_icon(nullptr)
	,health_bar(nullptr)
	,explosion(textures.get(Textures::Explosion))
{
	initAnimation();

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	fire_command.category = Category::SceneAirLayer;
	fire_command.action = [this, &textures](SceneNode& node, sf::Time)
	{
		createBullets(node, textures);
	};

	missile_command.category = Category::SceneAirLayer;
	missile_command.action = [this, &textures](SceneNode& node, sf::Time)
	{
		if(isAllied())
			createProjectile(node, Projectile::AlliedMissile, 0.f, 0.5f, textures);
		else
			createProjectile(node, Projectile::EnemyMissile, 0.f, 0.5f, textures);
	};

	pickup_command.category = Category::SceneAirLayer;
	pickup_command.action   = [this, &textures] (SceneNode& node, sf::Time)
	{
		createPickup(node, textures);
	};

	if (getCategory() == Category::PlayerAircraft)
	{
		std::unique_ptr<HealthNode> bar(new HealthNode(Table[type].hitpoints));
		health_bar = bar.get();
		health_bar->setPosition(0.f, 60.f);
		attachChild(std::move(bar));

		std::unique_ptr<TextNode> missile(new TextNode(fonts, ""));
		missile_display = missile.get();
		missile_display->setPosition(health_bar->getPosition().x, health_bar->getPosition().y - 20.f);
		attachChild(std::move(missile));

		std::unique_ptr<MissileIcon> icon(new MissileIcon(textures));
		missile_icon = icon.get();
		missile_icon->setPosition(missile_display->getPosition().x - 20.f, missile_display->getPosition().y);
		attachChild(std::move(icon));

		std::unique_ptr<PickupNode> pickup_display(new PickupNode(textures));
		pickup_bar = pickup_display.get();
		pickup_bar->setPosition(missile_display->getPosition().x + 20.f, missile_display->getPosition().y);
		attachChild(std::move(pickup_display));

		updatePlayerInterface();
	}
	if (type == Type::Boss)
	{
		missile_ammo = 50;
	}
}

void Aircraft::initAnimation()
{
	explosion.setFrameSize(sf::Vector2i(256, 256));
	explosion.setNumFrames(16);
	explosion.setScale(1.1f, 1.1f);
	explosion.setDuration(sf::seconds(1.2f));
	explosion.setPosition(0.f, -100.f);
	explosion.setOrigin(explosion.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	if (isDestroyed() && show_explosion)
		target.draw(explosion, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	
	updateRollAnimation();
	
	if(isDestroyed())
	{
		checkPickupDrop(commands);
		explosion.update(dt);
		return;
	}

	checkProjectileLaunch(dt, commands);

	if (isAllied())
		updatePlayerInterface();

	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);
}

void Aircraft::updatePlayerInterface()
{
	updateMissile();
	updatePickupBar();
	updateTexts();
	updateBar();
}

void Aircraft::updatePickupBar()
{
		pickup_bar->checkPickup(spread_level, fire_rate);
}

void Aircraft::updateMissile()
{
	if (missile_ammo != 0)
		missile_icon->setReady(missile_countdown);
	else
		missile_icon->sprite.setColor(sf::Color(255, 255, 255, 0));
}

void Aircraft::updateBar()
{
	health_bar->setSize(getHitpoints());
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
	if (fire_rate < 3)
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
	if (Table[type].fire_interval != sf::Time::Zero)
		is_firing = true;
}

void Aircraft::launchMissile()
{
	if (missile_ammo > 0 && Table[type].missile_interval != sf::Time::Zero)
		is_missile_launch = true;
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
	{
		fire();
		launchMissile();
	}

	if (is_firing && fire_countdown <= sf::Time::Zero)
	{
		commands.push(fire_command);
		fire_countdown += Table[type].fire_interval / (fire_rate + 1.f);
		is_firing = false;
	}
	else if (fire_countdown > sf::Time::Zero)
	{
		fire_countdown -= dt;
		is_firing = false;
	}

	if (is_missile_launch && missile_countdown <= sf::Time::Zero)
	{
		--missile_ammo;
		commands.push(missile_command);
		missile_countdown += Table[type].missile_interval / (fire_rate + 1.f);
		is_missile_launch = false;
	}
	else if (missile_countdown > sf::Time::Zero)
	{
		missile_countdown -= dt;
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
		if (missile_ammo == 0)
			missile_display->setString("");
		else
			missile_display->setString(std::to_string(missile_ammo));
}

void Aircraft::createPickup(SceneNode& node, const TextureHolder& textures) const
{
	auto type = static_cast<Pickup::Type>(Math::random(Pickup::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}

void Aircraft::updateRollAnimation()
{
	if (Table[type].roll_animation)
	{
		sf::IntRect textureRect = Table[type].texture_rect;

		if (getVelocity().x < 0.f)
			textureRect.left += textureRect.width;
		else if (getVelocity().x > 0.f)
			textureRect.left += 2 * textureRect.width;

		sprite.setTextureRect(textureRect);
	}
}