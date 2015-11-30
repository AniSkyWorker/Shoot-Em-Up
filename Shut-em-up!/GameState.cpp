#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
:State(stack, context)
,world(*context.window)
,player(*context.player)
{
}

void GameState::draw()
{
	world.draw();
}

bool GameState::update(sf::Time dt)
{


	world.update(dt);

	CommandQueue& commands = world.getCommandQueue();
	player.handleRealTimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = world.getCommandQueue();
	player.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		reqStackPush(States::pause);

	return true;
}
