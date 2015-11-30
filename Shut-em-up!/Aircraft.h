#pragma once
#include "Entity.h"
#include "ResourceIdientificators.h"
#include "TextNode.h"
#include "Data.h"

struct Aircraft : public Entity
{
	enum Type
	{
		Eagle,
		Raptor,
		Count
	};

	Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);

	void update();
	void updateMovement(sf::Time dt);

	Type Airtype;
	sf::Sprite sprite;
	TextNode* health_display;

	float travelled_dist;
	int direction_index;

	virtual unsigned int getCategory();
};
