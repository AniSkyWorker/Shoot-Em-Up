#pragma once
#include "Entity.h"
#include "ResourceIdientificators.h"
#include <SFML/Graphics.hpp>

struct Projectile : public Entity
{
	enum Type
	{
		AlliedBullet,
		EnemyBullet,
		Missile,
		TypeCount
	};

	Projectile(Type type, const TextureHolder& textures);

	void					guideTowards(sf::Vector2f position);
	bool					isGuided() const;

	virtual unsigned int	getCategory() const override;
	virtual sf::FloatRect	getBoundingRect() const override;
	float					getMaxSpeed() const;
	int						getDamage() const;


	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands) override;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;


	Type					type;
	sf::Sprite				sprite;
	sf::Vector2f			target_direction;
};

