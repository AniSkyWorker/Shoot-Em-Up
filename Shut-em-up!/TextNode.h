#pragma once
#include "SceneNode.h"
#include "ResourceIdientificators.h"
#include "ResourceHolder.h"

struct TextNode : public SceneNode
{
	TextNode(const FontHolder& fonts, const std::string& str);

	void setString(const std::string& str);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text text;
};

