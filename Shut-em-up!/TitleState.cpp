#include "TitleState.h"
#include "ResourceHolder.h"

TitleState::TitleState(StateStack& stack, Context context)
:State(stack, context)
,text()
,show_text(true)
,show_text_time(sf::Time::Zero)
{
	background_title.setTexture(context.textures->get(Textures::TitleScreen));

	text.setFont(context.fonts->get(Fonts::Main));
	text.setString("Press any key to start");
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(background_title);

	if (show_text)
		window.draw(text);
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		reqStackPop();
		reqStackPush(States::menu);
	}
	return true;
}

bool TitleState::update(sf::Time dt)
{
	show_text_time += dt;
	if (show_text_time >= sf::seconds(0.5f))
	{
		show_text = !show_text;
		show_text_time = sf::Time::Zero;
	}
	return true;
}
