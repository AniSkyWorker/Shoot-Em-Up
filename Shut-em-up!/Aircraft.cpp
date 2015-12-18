#include "Aircraft.h"
#include "ResourceHolder.h"
#include "CommandQueue.h"
#include "Data.h"

#include <cmath>
#include <iostream>

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
	,is_marked_for_remove(false)
	,sprite(textures.get(Table[type].texture))
	,fire_rate(1)
	,spread_level(1)
	,missile_ammo(20)
	,mDropPickupCommand()
	,travalled_distance(0.f)
	,direction_index(0)
	,missile_display(nullptr)
	,health_display(nullptr)
{
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

	mDropPickupCommand.category = Category::SceneAirLayer;
	/*	mDropPickupCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
	{
	createPickup(node, textures);
	};*/

	std::unique_ptr<TextNode> health(new TextNode(fonts, ""));
	health_display = health.get();
	attachChild(std::move(health));

	if (getCategory() == Category::PlayerAircraft)
	{
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
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	// Entity has been destroyed: Possibly drop pickup, mark for removal
	/*if (isDestroyed())
	{
	checkPickupDrop(commands);

	mIsMarkedForRemoval = true;
	return;
	}*/

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

/*bool Aircraft::isMarkedForRemoval() const
{
return mIsMarkedForRemoval;
}*/

bool Aircraft::isAllied() const
{
	return type == Eagle;
}

float Aircraft::getMaxSpeed() const
{
	return Table[type].speed;
}

/*void Aircraft::increaseFireRate()
{
if (mFireRateLevel < 10)
++mFireRateLevel;
}

void Aircraft::increaseSpread()
{
if (mSpreadLevel < 3)
++mSpreadLevel;
}

void Aircraft::collectMissiles(unsigned int count)
{
mMissileAmmo += count;
}
*/
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

		float radians = 3.14f / 180.f * (directions[direction_index].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		setVelocity(vx, vy);

		travalled_distance += getMaxSpeed() * dt.asSeconds();
	}
}

/*void Aircraft::checkPickupDrop(CommandQueue& commands)
{
if (!isAllied() && randomInt(3) == 0)
commands.push(mDropPickupCommand);
}*/

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

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * sprite.getGlobalBounds().width, yOffset * sprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectile->getMaxSpeed());

	float sign = isAllied() ? -1.f : +1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);
	node.attachChild(std::move(projectile));
}

void Aircraft::updateTexts()
{
	health_display->setString(std::to_string(getHitpoints()) + " HP");
	health_display->setPosition(0.f, 50.f);
	health_display->setRotation(-getRotation());

	if (missile_display)
	{
		if (missile_ammo == 0)
			missile_display->setString("");
		else
			missile_display->setString("M: " + std::to_string(missile_ammo));
	}
}

/*void Aircraft::createPickup(SceneNode& node, const TextureHolder& textures) const
{
auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));

std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
pickup->setPosition(getWorldPosition());
pickup->setVelocity(0.f, 1.f);
node.attachChild(std::move(pickup));
}*/


