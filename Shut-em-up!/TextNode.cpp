#include "TextNode.h"

TextNode::TextNode(const FontHolder& fonts, const std::string& str)
{
	text.setFont(fonts.get(Fonts::Main));
	text.setCharacterSize(15);
	setString(str);
}

void TextNode::setString(const std::string& str)
{
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}