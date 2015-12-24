#include "Projectile.h"
#include "Data.h"
#include "ResourceHolder.h"
#include "Math.h"

namespace
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures)
	:Entity(1)
	,type(type)
	,sprite(textures.get(Table[type].texture))
	,target_direction()
{
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().width / 2.f);
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

	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
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
