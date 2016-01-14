#include "Application.h"
#include "State.h"
#include "StateIdientificators.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "SettingsState.h"

const sf::Time Application::time_per_frame = sf::seconds(1.f / 60.f);

Application::Application() 
	:window(sf::VideoMode(1024, 760), "Steel Starling", sf::Style::Close)
	,textures()
	,fonts()
	,sounds()
	,player()
	,statistics_text()
	,statistics_num_frames(0)
	,state_stack(State::Context(window, textures, fonts, player, music, sounds))
{
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	fonts.load(Fonts::Main, "Media/Sansation.ttf");
	textures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.jpg");
	textures.load(Textures::ButtonNormal, "Media/Textures/ButtonNormal.png");
	textures.load(Textures::ButtonPressed, "Media/Textures/ButtonPressed.png");
	textures.load(Textures::ButtonSelected, "Media/Textures/ButtonSelected.png");

	statistics_text.setFont(fonts.get(Fonts::Main));
	statistics_text.setPosition(5.f, 5.f);
	statistics_text.setCharacterSize(10);

	registerStates();
	state_stack.pushState(States::title);
	music.setVolume(25.f);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Time elapsed_time = clock.restart();
		time_since_last_update += elapsed_time;
		while (time_since_last_update > time_per_frame)
		{
			time_since_last_update -= time_per_frame;
			
			processEvents();
			update(time_per_frame);
			
			if (state_stack.isEmpty())
				window.close();
		}
		updateStatistics(elapsed_time);
		render();
	}
}

void Application::processEvents()
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		state_stack.handleEvent(event);
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Application::update(sf::Time dt)
{
	state_stack.update(dt);
}

void Application::render()
{
	window.clear();
	state_stack.draw();
	window.setView(window.getDefaultView());
	window.draw(statistics_text);
	window.display();
}
void Application::updateStatistics(sf::Time elapsed_time)
{
	statistics_update_time += elapsed_time;
	statistics_num_frames += 1;

	if (statistics_update_time >= sf::seconds(1.0f))
	{
		statistics_text.setString("FPS = " + std::to_string(statistics_num_frames));

		statistics_update_time -= sf::seconds(1.0f);
		statistics_num_frames = 0;
		
	}
}
void Application::registerStates()
{
	state_stack.registerState<GameState>(States::game);
	state_stack.registerState<MenuState>(States::menu);
	state_stack.registerState<TitleState>(States::title);
	state_stack.registerState<PauseState>(States::pause);
	state_stack.registerState<GameOverState>(States::gameover);
	state_stack.registerState<SettingsState>(States::settings);
}
