#pragma once
#include "SceneNode.h"
struct Entity : public SceneNode
{
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float x, float y);
	sf::Vector2f getVelocity() const;
	sf::Vector2f vector_velocity;

    virtual void updateCurrent(sf::Time dt);
};