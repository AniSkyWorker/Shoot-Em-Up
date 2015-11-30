#pragma once

#include <memory>
#include "StateIdientificators.h"
#include "ResourceIdientificators.h"

namespace sf
{
	class RenderWindow;
	class Event;
	class Time;
}

struct StateStack;
struct Player;

struct State
{
	typedef std::unique_ptr<State> ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
	};

	State(StateStack& stack, Context context);
	virtual ~State();
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

	void reqStackPush(States::ID state_id);
	void reqStackPop();
	void reqStateClear();

	Context getContext() const;

	StateStack* state_stack;
	Context object_context;
};

