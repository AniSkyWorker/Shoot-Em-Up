#pragma once

#include "State.h"
#include "Player.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"

#include <SFML/Graphics.hpp>
#include <array>


struct SettingsState : public State
{
	SettingsState(StateStack& stack, Context context);

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

	void updateLabels();
	void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

	sf::Sprite background_sprite;
	GUI::Container GUI_container;
	std::array<GUI::Button::Ptr, Player::ActionCount> binding_buttons;
	std::array<GUI::Label::Ptr, Player::ActionCount> binding_labels;
};