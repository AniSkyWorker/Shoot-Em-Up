#include "StateStack.h"
#include <cassert>

StateStack::StateStack(State::Context context)
	:stack()
	,pending_list()
	,context(context)
	,factories()
{
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::Ptr& state : stack)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	pending_list.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	pending_list.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	pending_list.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = factories.find(stateID);
	assert(found != factories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : pending_list)
	{
		switch (change.action)
		{
		case Push:
			stack.push_back(createState(change.stateID));
			break;

		case Pop:
			stack.pop_back();
			break;

		case Clear:
			stack.clear();
			break;
		}
	}

	pending_list.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	:action(action)
	,stateID(stateID)
{
}