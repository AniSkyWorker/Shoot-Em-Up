#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"

struct GameState: public State
{
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	World world;
	Player& player;
};

