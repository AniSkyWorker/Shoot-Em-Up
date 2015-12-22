#include "Projectile.h"
#include "Data.h"
#include "ResourceHolder.h"

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
	target_direction = unit_vector / std::sqrt(unit_vector.x * unit_vector.x + unit_vector.y* unit_vector.y);
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
		sf::Vector2f new_velocity = unit_vector / std::sqrt(unit_vector.x * unit_vector.x + unit_vector.y* unit_vector.y);;
		new_velocity *= getMaxSpeed();
		float angle = std::atan2(new_velocity.y, new_velocity.x);

		setRotation(180.f / 3.14f * angle + 90.f);
		setVelocity(new_velocity);
	}

	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Projectile::getCategory() const
{
	if (type == EnemyBullet)
		return Category::EnemyProjectile;
	else
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
