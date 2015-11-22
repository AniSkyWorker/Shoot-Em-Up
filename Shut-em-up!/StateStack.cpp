#include "StateStack.h"
#include <cassert>

StateStack::StateStack(State::Context context)
	: stack()
	, pending_list()
	, context(context)
	, factories()
{
}
StateStack::PendingChanges::PendingChanges(Action action, States::ID state_ID = States::none)
	:action(action)
	, state_ID(state_ID)
{
}

State::ptr StateStack::createState(States::ID stateID)
{
	auto found = factories.find(stateID);
	assert(found != factories.end());

	return found->second();
}

void StateStack::pushState(States::ID state_ID)
{
	pending_list.push_back(PendingChanges(push, state_ID));
}

void StateStack::popState()
{
	pending_list.push_back(PendingChanges(pop));
}

void StateStack::clearState()
{
	pending_list.push_back(PendingChanges(clear));
}


void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->handleEvent(event))
			break;
	applyPendingChanges();
}
void StateStack::update(sf::Time dt)
{
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->update(dt))
			break;
	applyPendingChanges();
}
void StateStack::draw()
{
	for (State::ptr& state : stack)
		state->draw();
}
void StateStack::applyPendingChanges()
{
	for (PendingChanges change : pending_list)
	{
		switch (change.action)
		{
		case pop:
			stack.pop_back();
			break;
		case push:
			stack.push_back(createState(change.state_ID));
			break;
		case clear:
			stack.clear();
			break;
		}
	}
	pending_list.clear();
}

bool StateStack::isEmpty() const
{
	return stack.empty();
}
