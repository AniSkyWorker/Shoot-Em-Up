#include "MenuState.h"
#include "Button.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
	:State(stack, context)
	,GUI_container()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	background_sprite.setTexture(texture);

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(100, 300);
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition(100, 350);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		//requestStackPush(States::settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 400);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	GUI_container.pack(playButton);
	GUI_container.pack(settingsButton);
	GUI_container.pack(exitButton);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(background_sprite);
	window.draw(GUI_container);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	GUI_container.handleEvent(event);
	return false;
}
