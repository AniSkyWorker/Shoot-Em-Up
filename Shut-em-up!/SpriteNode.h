#pragma once

#include "SceneNode.h"
#include <SFML/Graphics.hpp>
struct SpriteNode : public SceneNode
{
	
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite sprite;
};
