#pragma once

#include "SceneNode.h"

struct HealthNode : public SceneNode
{
	HealthNode(const int& max_hp);

	void setSize(const int& hitpoints);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape background_shape;
	sf::RectangleShape hp_shape;
};

