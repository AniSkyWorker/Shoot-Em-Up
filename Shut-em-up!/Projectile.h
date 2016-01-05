#pragma once

#include "Entity.h"
#include"Animation.h"
#include "ResourceIdientificators.h"
#include <SFML/Graphics.hpp>

struct Projectile : public Entity
{
	enum Type
	{
		AlliedBullet,
		EnemyBullet,
		AlliedMissile,
		EnemyMissile,
		TypeCount
	};

	Projectile(Type type, const TextureHolder& textures);

	void guideTowards(sf::Vector2f position);
	bool isGuided() const;

	virtual unsigned int getCategory() const override;
	virtual sf::FloatRect getBoundingRect() const override;
	float getMaxSpeed() const;
	int	getDamage() const;

	virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool isMarkedForRemoval() const override;

	Type type;
	sf::Sprite sprite;
	sf::Vector2f target_direction;

	Animation explosion;
	bool show_explosion;
};

