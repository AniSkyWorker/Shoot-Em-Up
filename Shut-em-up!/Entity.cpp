#include "Entity.h"
#include <cassert>

Entity::Entity(int hitpoints)
	:velocity()
	,hitpoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

void Entity::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity;
}

void Entity::accelerate(sf::Vector2f vel)
{
	velocity += vel;
}

void Entity::accelerate(float vx, float vy)
{
	velocity.x += vx;
	velocity.y += vy;
}

int Entity::getHitpoints() const
{
	return hitpoints;
}

void Entity::repair(int points)
{
	assert(points > 0);

	hitpoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);

	hitpoints -= points;
}

void Entity::destroy()
{
	hitpoints = 0;
}

bool Entity::isDestroyed() const
{
	return hitpoints <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
	move(velocity * dt.asSeconds());
}

void Entity::remove()
{
	destroy();
}