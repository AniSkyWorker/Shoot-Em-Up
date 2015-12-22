#pragma once
#include "ResourceIdientificators.h"
#include "Entity.h"

struct Aircraft;

struct Pickup : public Entity
{
	enum Type
	{
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		TypeCount
	};

	Pickup(Type type, const TextureHolder& textures);

	virtual unsigned int getCategory() const override;
	virtual sf::FloatRect getBoundingRect() const override;

	void apply(Aircraft& player) const;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	Type type;
	sf::Sprite sprite;
};

