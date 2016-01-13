#include "GameOverState.h"
#include "Player.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>



GameOverState::GameOverState(StateStack& stack, Context context)
	:State(stack, context)
	,gameover_text()
	,instructions_text()
	,elapsed_time(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f view_size = context.window->getView().getSize();

	gameover_text.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
		gameover_text.setString("Mission failed!");
	else
		gameover_text.setString("Mission successful!");
	gameover_text.setCharacterSize(70);
	gameover_text.setOrigin(gameover_text.getLocalBounds().width / 2.f, gameover_text.getLocalBounds().height / 2.f);
	gameover_text.setPosition(0.5f * view_size.x, 0.4f * view_size.y);

	instructions_text.setFont(font);
	instructions_text.setString("(Press Enter to return to main menu)");
	instructions_text.setOrigin(instructions_text.getGlobalBounds().width / 2.f, instructions_text.getGlobalBounds().height / 2.f);
	instructions_text.setPosition(0.5f * view_size.x, 0.6f * view_size.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameover_text);
	window.draw(instructions_text);
}

bool GameOverState::update(sf::Time dt)
{
	return false;
}

bool GameOverState::handleEvent(const sf::Event&event)
{
	if(event.type == sf::Event::KeyReleased)
		if (event.key.code == sf::Keyboard::Return)
		{
			requestStateClear();
			requestStackPush(States::menu);
		}
	return false;
}
