#include "HealthNode.h"

HealthNode::HealthNode(const int& max_hp)
{
	background_shape.setSize(sf::Vector2f(10, max_hp / 2.f));
	background_shape.setOutlineColor(sf::Color::Green);
	background_shape.setFillColor(sf::Color::White);
	background_shape.setOrigin(background_shape.getSize() / 2.f);
	background_shape.setRotation(-90);

	hp_shape.setSize(sf::Vector2f(10, 0));
	hp_shape.setFillColor(sf::Color::Red);
	hp_shape.setRotation(-90);
	hp_shape.setPosition(background_shape.getPosition().x - background_shape.getGlobalBounds().width / 2.f,
		background_shape.getPosition().y + background_shape.getGlobalBounds().height / 2.f);

	background_shape.setOutlineThickness(2);
}

void HealthNode::setSize(const int& hitpoints)
{
	if(hitpoints < 0)
		hp_shape.setSize(sf::Vector2f(10, 0));
	else
		hp_shape.setSize(sf::Vector2f(10, hitpoints / 2.f));
}

void HealthNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_shape, states);
	target.draw(hp_shape, states);
}