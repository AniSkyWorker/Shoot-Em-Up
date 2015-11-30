#pragma once
#include "SceneNode.h"
struct Entity : public SceneNode
{
	Entity(int hitpoints);
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float x, float y);

    virtual void updateCurrent(sf::Time dt);

	void damage(int points);
	void repair(int points);
	void destroy();

	sf::Vector2f getVelocity() const;
	int getHitpoints() const;
	bool isDestroyed() const;

	sf::Vector2f vector_velocity;
	int hitpoints;
};