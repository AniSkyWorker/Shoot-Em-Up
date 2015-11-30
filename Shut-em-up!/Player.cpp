#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.h"

#include <map>
#include <algorithm>
struct AircraftMover
{
	AircraftMover(float velocity_x, float velocity_y)
		:velocity(velocity_x, velocity_y)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.setVelocity(aircraft.getVelocity() + velocity);
	}

	sf::Vector2f velocity;
};
Player::Player()
{

	key_binding[sf::Keyboard::Left] = moveLeft;
	key_binding[sf::Keyboard::Right] = moveRight;
	key_binding[sf::Keyboard::Up] = moveUp;
	key_binding[sf::Keyboard::Down] = moveDown;

	initActions();

	for (auto& pair : action_binding)
		pair.second.category = Category::player_aircraft;
}
void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (auto pair : key_binding)
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeHandle(pair.second))
			commands.push(action_binding[pair.second]);
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = key_binding.find(event.key.code);
		if (found != key_binding.end() && !isRealTimeHandle(found->second))
			commands.push(action_binding[found->second]);
	}
}

void Player::assignKey(Actions action, sf::Keyboard::Key key)
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

sf::Keyboard::Key Player::getAssignKey(Actions action) const
{
	for (auto pair : key_binding)
		if (pair.second == action)
			return pair.first;
	return sf::Keyboard::Unknown;
}

bool Player::isRealTimeHandle(Actions action)
{
	switch (action)
	{
	case moveLeft:
	case moveRight:
	case moveDown:
	case moveUp:
		return true;

	default:
		return false;
	}
}
void Player::initActions()
{
	const float playerSpeed = 200.f;
	
	action_binding[moveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	action_binding[moveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	action_binding[moveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	action_binding[moveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}