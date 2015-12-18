#pragma once
#include "SceneNode.h"

struct Entity : public SceneNode
{
	Entity(int hitpoints);

	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float vx, float vy);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	sf::Vector2f		getVelocity() const;

	int					getHitpoints() const;
	void				repair(int points);
	void				damage(int points);
	void				destroy();
	virtual bool		isDestroyed() const;


	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);

	sf::Vector2f		mVelocity;
	int					mHitpoints;
};