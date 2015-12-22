#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.h"

#include <map>
#include <algorithm>

using namespace std::placeholders;


struct AircraftMover
{
	AircraftMover(float vx, float vy)
		:velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity * aircraft.getMaxSpeed());
	}

	sf::Vector2f velocity;
};

Player::Player()
	:current_status(MissionRunning)
{
	key_binding[sf::Keyboard::Left] = MoveLeft;
	key_binding[sf::Keyboard::Right] = MoveRight;
	key_binding[sf::Keyboard::Up] = MoveUp;
	key_binding[sf::Keyboard::Down] = MoveDown;
	key_binding[sf::Keyboard::Space] = Fire;
	key_binding[sf::Keyboard::M] = LaunchMissile;

	initializeActions();

	for (auto& pair : action_binding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = key_binding.find(event.key.code);
		if (found != key_binding.end() && !isRealtimeAction(found->second))
			commands.push(action_binding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : key_binding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(action_binding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto itr = key_binding.begin(); itr != key_binding.end(); )
	{
		if (itr->second == action)
			key_binding.erase(itr++);
		else
			++itr;
	}
	key_binding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : key_binding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	current_status = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return current_status;
}

void Player::initializeActions()
{
	action_binding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1, 0));
	action_binding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+1, 0));
	action_binding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0, -1));
	action_binding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0, +1));
	action_binding[Fire].action = derivedAction<Aircraft>(std::bind(&Aircraft::fire, _1));
	action_binding[LaunchMissile].action = derivedAction<Aircraft>(std::bind(&Aircraft::launchMissile, _1));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
	case Fire:
		return true;

	default:
		return false;
	}
}