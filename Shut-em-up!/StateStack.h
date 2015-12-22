#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "State.h"
#include "StateIdientificators.h"
#include "ResourceIdientificators.h"
#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

struct StateStack : private sf::NonCopyable
{
	enum Action
	{
		Push,
		Pop,
		Clear,
	};
	StateStack(State::Context context);

	template <typename T>
	void registerState(States::ID stateID);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();


	struct PendingChange
	{
		PendingChange(Action action, States::ID stateID = States::none);

		Action action;
		States::ID stateID;
	};

	std::vector<State::Ptr>	stack;
	std::vector<PendingChange> pending_list;

	State::Context context;
	std::map<States::ID, std::function<State::Ptr()>> factories;
};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	factories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, context));
	};
}
