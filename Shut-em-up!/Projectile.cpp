#include "Projectile.h"
#include "Data.h"
#include "ResourceHolder.h"
#include "Math.h"
#include "EmitterNode.h"

namespace
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures)
	:Entity(1)
	,type(type)
	,sprite(textures.get(Table[type].texture))
	,target_direction()
	,show_explosion(true)
	,explosion(textures.get(Textures::Explosion))
{
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().width / 2.f);

	explosion.setFrameSize(sf::Vector2i(256, 256));
	explosion.setNumFrames(16);
	explosion.setOrigin(explosion.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	if (isGuided())
	{
		
		explosion.setPosition(0.f, -100.f);
		explosion.setDuration(sf::seconds(0.5f));
		

		std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Smoke));
		smoke->setPosition(0.f, getBoundingRect().height / 2.f);
		attachChild(std::move(smoke));

		std::unique_ptr<EmitterNode> propellant(new EmitterNode(Particle::Propellant));
		propellant->setPosition(0.f, getBoundingRect().height / 2.f);
		attachChild(std::move(propellant));
	}
	else
	{
		explosion.setScale(0.2f, 0.2f);
		explosion.setDuration(sf::seconds(0.5f));
		explosion.setPosition(0.f, -20.f);
	}
}

void Projectile::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	sf::Vector2f unit_vector = position - getWorldPosition();
	target_direction = Math::normalized(unit_vector);
}

bool Projectile::isGuided() const
{
	return type == Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	
	if (isGuided())
	{
		const float approachRate = 200.f;
		sf::Vector2f unit_vector = (approachRate * dt.asSeconds() * target_direction + getVelocity());
		sf::Vector2f new_velocity = Math::normalized(unit_vector);
		new_velocity *= getMaxSpeed();
		setRotation(Math::polarAngle(new_velocity));
		setVelocity(new_velocity);
	}
	if (isDestroyed())
	{
		explosion.update(dt);
		if (!isGuided())
			return;
	}
	
	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	if (isDestroyed() && show_explosion)
		target.draw(explosion, states);
}

unsigned Projectile::getCategory() const
{
	if (type == EnemyBullet)
		return Category::EnemyProjectile;
	return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return Table[type].speed;
}

int Projectile::getDamage() const
{
	return Table[type].damage;
}

bool Projectile::isMarkedForRemoval() const
{
	return isDestroyed() && (explosion.isFinished());
}