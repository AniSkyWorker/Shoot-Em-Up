#pragma once

#include "SceneNode.h"
#include <SFML/Graphics.hpp>

struct SpriteNode : public SceneNode
{
	SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite sprite;
};
