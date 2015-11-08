#pragma once
#include "SceneNode.h"

struct SpriteNode : public SceneNode
{
	sf::Sprite sprite;
	SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

