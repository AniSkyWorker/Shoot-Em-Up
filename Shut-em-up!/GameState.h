#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"

struct GameState : public State
{
	GameState(StateStack& stack, Context context);

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

	World world;
	Player&	player;
};
