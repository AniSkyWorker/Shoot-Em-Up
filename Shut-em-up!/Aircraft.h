#pragma once
#include "Entity.h"
#include "ResourceIdientificators.h"

struct Aircraft : public Entity
{
	enum Type
	{
		Eagle,
		Raptor,
	};

	Aircraft(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	Type Airtype;
	sf::Sprite sprite;

	
};
