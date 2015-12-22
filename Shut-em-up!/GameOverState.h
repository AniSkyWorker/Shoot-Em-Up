#pragma once
#include "State.h"

struct GameOverState : public State
{
	GameOverState(StateStack& stack, Context context);

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

	sf::Text text;
	sf::Time elapsed_time;
};

