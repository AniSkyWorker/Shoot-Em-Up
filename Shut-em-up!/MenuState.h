#pragma once

#include "State.h"
#include "Container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

struct MenuState : public State
{
		MenuState(StateStack& stack, Context context);

		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(const sf::Event& event);

		sf::Sprite background_sprite;
		GUI::Container GUI_container;
};

