#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>

struct  KeyboardKeys
{
	KeyboardKeys() = delete;

	static std::string getKeyName(const sf::Keyboard::Key key);
};

