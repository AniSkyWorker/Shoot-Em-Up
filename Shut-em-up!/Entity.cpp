#include "Entity.h"
#include <SFML/Graphics.hpp>

void Entity::setVelocity(sf::Vector2f velocity)
{
	velocity = vector_velocity;
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

void Entity::updateCurrent(sf::Time dt)
{
	move(vector_velocity * dt.asSeconds());
}