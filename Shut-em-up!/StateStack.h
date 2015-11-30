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


struct StateStack: private sf::NonCopyable
{
	enum Action
	{
		push,
		pop,
		clear,
	};

	StateStack(const State::Context context);

	template <typename T> void registerState(States::ID state_ID)
	{
		factories[state_ID] = [this]()
		{
			return State::ptr(new T(*this, context));
		};
	}
	
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(States::ID state_ID);
	void popState();
	void clearState();

	bool isEmpty() const;

	State::ptr createState(States::ID state_ID);
	void applyPendingChanges();

	struct PendingChanges
	{
		PendingChanges(Action action, States::ID stateID);
		Action action;
		States::ID state_ID;
	};

	std::vector<State::ptr> stack;
	std::vector<PendingChanges> pending_list;
	State::Context context;
	std::map<States::ID, std::function<State::ptr()>> factories;
};

