#pragma once
#include "State.h"
#include "SFML\Graphics.hpp"

struct PauseState: public State
{
	PauseState(StateStack& stack, Context context);
	~PauseState();

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

	sf::Text paused_text;
	sf::Text instructions;
};

