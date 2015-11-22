#pragma once
#include "State.h"
#include "SFML\Graphics.hpp"

struct MenuState: public State
{
	enum OptionNames
	{
		Play,
		Exit,
	};
	
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void updateOptionText();

	sf::Sprite background_sprite;
	std::vector<sf::Text> options;
	std::size_t index;
};

