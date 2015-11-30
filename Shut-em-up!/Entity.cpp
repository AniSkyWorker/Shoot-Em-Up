#include "Entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity(int hitpoints)
:vector_velocity()
,hitpoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	vector_velocity = velocity;
}
void Entity::setVelocity(float x, float y)
{
	vector_velocity.x = x;
	vector_velocity.y = y;
}
sf::Vector2f Entity::getVelocity() const
{
	return vector_velocity;
}

int Entity::getHitpoints() const
{
	return hitpoints;
}
void Entity::damage(int points)
{
	hitpoints -= points;
}
void Entity::repair(int points)
{
	hitpoints += points;
}
bool Entity::isDestroyed() const
{
	return hitpoints <= 0;
}
void Entity::destroy()
{
	hitpoints = 0;
}

void Entity::updateCurrent(sf::Time dt)
{
	move(vector_velocity * dt.asSeconds());
}