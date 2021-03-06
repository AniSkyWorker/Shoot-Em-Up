#include "PauseState.h"
#include "ResourceHolder.h"

PauseState::PauseState(StateStack& stack, Context context)
	:State(stack, context)
	,paused_text()
	,instructions()
{
	sf::Vector2f view_size = context.window->getView().getSize();
	sf::Font& font = context.fonts->get(Fonts::Main);

	paused_text.setFont(font);
	paused_text.setString("Game Paused");
	paused_text.setCharacterSize(70);
	paused_text.setOrigin(paused_text.getLocalBounds().width / 2.f, paused_text.getLocalBounds().height / 2.f);
	paused_text.setPosition(0.5f * view_size.x, 0.4f * view_size.y);

	instructions.setFont(font);
	instructions.setString("(Press Escape to return to the main menu, Enter - to resume)");
	instructions.setOrigin(instructions.getLocalBounds().width / 2.f, instructions.getLocalBounds().height / 2.f);
	instructions.setPosition(0.5f * view_size.x, 0.6f * view_size.y);

	getContext().music->setPaused(true);
}

PauseState::~PauseState()
{
	getContext().music->setPaused(false);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	sf::RectangleShape background_shape;
	background_shape.setFillColor(sf::Color(0,0,0,150));
	background_shape.setSize(sf::Vector2f(window.getSize()));

	window.draw(background_shape);
	window.draw(paused_text);
	window.draw(instructions);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		requestStackPop();
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStateClear();
		requestStackPush(States::menu);
	}

	return false;
}