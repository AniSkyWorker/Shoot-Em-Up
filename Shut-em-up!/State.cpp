#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music, SoundPlayer& sounds)
	:window(&window)
	,textures(&textures)
	,fonts(&fonts)
	,player(&player)
	,music(&music)
	,sounds(&sounds)
{
}

State::State(StateStack& stack, Context context)
	:stack(&stack)
	,context(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	stack->pushState(stateID);
}

void State::requestStackPop()
{
	stack->popState();
}

void State::requestStateClear()
{
	stack->clearStates();
}

State::Context State::getContext() const
{
	return context;
}
