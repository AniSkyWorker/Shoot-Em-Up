#pragma once

#include "SceneNode.h"
#include "ResourceIdientificators.h"
#include "Pickup.h"

struct PickupNode :	public SceneNode
{
	PickupNode(const TextureHolder& textures);

	void checkPickup(int spread_lvl, int fire_rate);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite spread_sprite;
	sf::Sprite rate_sprite;

};

