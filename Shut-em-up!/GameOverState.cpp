#include "GameOverState.h"
#include "Player.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>



GameOverState::GameOverState(StateStack& stack, Context context)
	:State(stack, context)
	,text()
	, elapsed_time(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	text.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
		text.setString("Mission failed!");
	else
		text.setString("Mission successful!");

	text.setCharacterSize(70);
	text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
	text.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(text);
}

bool GameOverState::update(sf::Time dt)
{
	elapsed_time += dt;
	if (elapsed_time > sf::seconds(5))
	{
		requestStateClear();
		requestStackPush(States::menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}
