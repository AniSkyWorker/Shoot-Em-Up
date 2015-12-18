#pragma once

#include <memory>
#include "StateIdientificators.h"
#include "ResourceIdientificators.h"
#include <SFML/Graphics.hpp>
namespace sf
{
	class RenderWindow;
}

struct StateStack;
struct Player;

struct State
{
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		Player*				player;
	};

	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;

	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;

	StateStack*			mStack;
	Context				mContext;
};

