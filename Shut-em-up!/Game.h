#pragma once

#include "World.h"
#include <SFML/Graphics.hpp>
struct Game : private sf::NonCopyable
{
	Game();
	void run();
	void processEvents();
	void update(sf::Time time_per_frame);
	void render();
	void updateStatistics(sf::Time elapsed_time);
	private:
		sf::RenderWindow window;
		World world;
		sf::Font font;
		sf::Text statistics_text;
		sf::Time statistics_update_time;
		std::size_t	statistics_num_frames;
};