#pragma once
#include "SceneNode.h"
#include "ResourceIdientificators.h"

struct MissileIcon : public SceneNode
{
	MissileIcon(const TextureHolder& textures);
	void setReady(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};

