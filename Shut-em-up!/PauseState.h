#pragma once
#include "State.h"
#include "SFML\Graphics.hpp"
struct PauseState: public State
{
	PauseState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	sf::Text			paused_text;
	sf::Text			instructions;
};

