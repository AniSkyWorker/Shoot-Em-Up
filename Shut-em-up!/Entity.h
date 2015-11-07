#ifndef ENTITY_H
#define ENTITY_H
#include "SceneNode.h"
struct Entity : public SceneNode
{
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float x, float y);
	sf::Vector2f getVelocity() const;
	sf::Vector2f vector_velocity;

	void updateCurrent(sf::Time dt);
};
#endif // ENTITY_H