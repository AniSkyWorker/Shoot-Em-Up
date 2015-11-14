#include "Game.h"

const sf::Time time_per_frame = sf::seconds(1.f / 60.f);

Game::Game() : window(sf::VideoMode(640, 480), "Shoot them!!!", sf::Style::Close)
, font()
, statistics_text()
, world(window)
{
	if(!font.loadFromFile("Media/Sansation.ttf"))
	{
		//handle error
	}
	statistics_text.setFont(font);
	statistics_text.setPosition(5.f, 5.f);
	statistics_text.setCharacterSize(7);
}
void Game::run()
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
		}

		updateStatistics(elapsed_time);
		render();
	}
}
void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch(event.type)
		{
			/*case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code);
				break;*/
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}
void Game::update(sf::Time elapsed_time)
	{
		world.update(elapsed_time);
	}
void Game::render()
	{
		
		window.clear();
		world.draw();
		window.setView(window.getDefaultView());
		SceneNode SceneGraph;
		window.draw(SceneGraph);
		window.draw(statistics_text);
		window.display();

	}
void Game::updateStatistics(sf::Time elapsed_time)
	{

		statistics_update_time += elapsed_time;
		statistics_num_frames += 1;

		if (statistics_update_time >= sf::seconds(1.0f))
		{
			statistics_text.setString(
				"Frames / Second = " + std::to_string(statistics_num_frames) + "\n" +
				"Time / Update = " + std::to_string(statistics_update_time.asMicroseconds() / statistics_num_frames) + "micros");

			statistics_update_time -= sf::seconds(1.0f);
			statistics_num_frames = 0;
		
		}
	}
