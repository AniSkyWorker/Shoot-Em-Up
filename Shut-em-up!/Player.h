#pragma once
#include "Command.h"
#include <functional>
#include <map>
#include "CommandQueue.h"

struct Player
{
	Player();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealTimeInput(CommandQueue& commands);

	enum Actions
	{
		moveLeft,
		moveRight,
		moveUp,
		moveDown,
		count,
	};

	void assignKey(Actions action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignKey(Actions action) const;
	void initActions();
	bool isRealTimeHandle(Actions action);
	std::map<sf::Keyboard::Key, Actions> key_binding;
	std::map<Actions, Command> action_binding;
};

