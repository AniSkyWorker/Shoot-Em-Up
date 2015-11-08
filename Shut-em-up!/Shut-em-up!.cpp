#include <SFML/Graphics.hpp>
#include <iostream>

const float player_speed = 100.f;
const sf::Time time_per_frame = sf::seconds(1.f / 60.f);
struct Game {
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Sprite player;
	sf::Font font;
	sf::Text statistics_text;
	sf::Time statistics_update_time;
	std::size_t	statistics_num_frames;

	Game()
		: window(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
		, texture()
		, player()
		, font()
		, statistics_text()
	{
		if (!texture.loadFromFile("Media/textures/Eagle.png"))
		{
			//Handle Error
		}
		player.setTexture(texture);
		player.setPosition(100.f, 100.f);

		if(!font.loadFromFile("Media/Sansation.ttf"))
		{
			//handle error
		}
		statistics_text.setFont(font);
		statistics_text.setPosition(5.f, 5.f);
		statistics_text.setCharacterSize(7);
	}
	void run()
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
				render();
				updateStatistics(elapsed_time);
		}
	}
	void processEvents()
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
	void update(sf::Time time_per_frame)
	{
		
		sf::Vector2f movement(0.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)))
			movement.x -= player_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
			movement.x += player_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)))
			movement.y -= player_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)))
			movement.y += player_speed;

		player.move(movement * time_per_frame.asSeconds());

	}
	void render()
	{
		
		window.clear();
		window.draw(statistics_text);
		window.draw(player);
		window.display();

	}
	void updateStatistics(sf::Time elapsed_time)
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
};

int main()
{
	try 
	{
		Game game;
		game.run();
	}
	catch (std::exeption& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	
}