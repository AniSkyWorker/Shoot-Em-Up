#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
	:State(stack, context)
	,world(*context.window, *context.fonts, *context.sounds)
	,player(*context.player)
{
	player.setMissionStatus(Player::MissionRunning);
	context.music->setVolume(70.f);
	context.music->play(Music::MissionTheme);
}

void GameState::draw()
{
	world.draw();
}

bool GameState::update(sf::Time dt)
{
	world.update(dt);
	
	if (!world.hasPlayerAlive())
	{
		player.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::gameover);
	}
	else if (world.hasPlayerReachedEnd())
	{
		player.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::gameover);
	}

	CommandQueue& commands = world.getCommandQueue();
	player.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = world.getCommandQueue();
	player.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::pause);

	return true;
}
