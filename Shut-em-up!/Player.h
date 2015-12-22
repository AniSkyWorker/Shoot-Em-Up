#pragma once

#include "Command.h"
#include <SFML/Graphics.hpp>
#include <map>

struct CommandQueue;

struct Player
{
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		ActionCount
	};

	enum MissionStatus
	{
		MissionRunning,
		MissionSuccess,
		MissionFailure
	};

	Player();

	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	void setMissionStatus(MissionStatus status);
	MissionStatus getMissionStatus() const;

	void initializeActions();
	static bool isRealtimeAction(Action action);


	std::map<sf::Keyboard::Key, Action>	key_binding;
	std::map<Action, Command> action_binding;
	MissionStatus current_status;
};


