#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, Context context)
:state_stack(&stack)
,object_context(context)
{
}

State::~State()
{
}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
:window(&window)
,textures(&textures)
,fonts(&fonts)
,player(&player)
{
}

void State::reqStackPush(States::ID stateID)
{
	state_stack->pushState(stateID);
}

void State::reqStackPop()
{
	state_stack->popState();
}

void State::reqStateClear()
{
	state_stack->clearState();
}

State::Context State::getContext() const
{
	return object_context;
}
