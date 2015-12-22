#pragma once

#include "State.h"
#include "SFML\Graphics.hpp"

struct TitleState: public State
{
	TitleState(StateStack& stack, Context context);

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

	sf::Sprite background_title;
	sf::Text text;

	bool show_text;
	sf::Time show_text_time;
};

