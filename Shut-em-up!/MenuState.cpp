#include "MenuState.h"
#include "ResourceHolder.h"

MenuState::MenuState(StateStack& stack, Context context)
:State(stack, context)
,index(0)
,options()
{
	background_sprite.setTexture(context.textures->get(Textures::TitleScreen));

	sf::Text play;
	play.setFont(context.fonts->get(Fonts::Main));
	play.setString("Play");
	play.setOrigin(play.getLocalBounds().width / 2.f, play.getLocalBounds().height / 2.f);
	play.setPosition(context.window->getView().getSize() / 2.f);
	options.push_back(play);

	sf::Text exit;
	exit.setFont(context.fonts->get(Fonts::Main));
	exit.setString("Exit");
	play.setOrigin(exit.getLocalBounds().width / 2.f, exit.getLocalBounds().height / 2.f);
	exit.setPosition(play.getPosition() + sf::Vector2f(0.f, 30.f));
	options.push_back(exit);

	updateOptionText();

}

void MenuState::updateOptionText()
{
	if (options.empty())
		return;

	for(sf::Text& text : options)
		text.setColor(sf::Color::White);

	options[index].setColor(sf::Color::Red);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(background_sprite);

	for(const sf::Text& text : options)
		window.draw(text);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Up)
	{
		if (index > 0)
			index--;
		else
			index = options.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (index < options.size() - 1)
			index++;
		else
			index = 0;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Return)
	{
		if (index == Play)
		{
			reqStackPop();
			reqStackPush(States::loading);
		}
		else if (index == Exit)
		{
			reqStackPop();
		}
	}
	return true;
}