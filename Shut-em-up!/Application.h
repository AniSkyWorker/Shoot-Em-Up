#pragma once
#include <SFML/Graphics.hpp>
#include <vld.h>

#include "Player.h"
#include "StateStack.h"
#include "ResourceIdientificators.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

struct Application
{
	Application();

	void run();
	void processEvents();
	void update(sf::Time time_per_frame);
	void render();

	void updateStatistics(sf::Time elapsed_time);

	void registerStates();

	sf::RenderWindow window;

	sf::Text statistics_text;
	sf::Time statistics_update_time;
	std::size_t	statistics_num_frames;

	static const sf::Time	time_per_frame;

	Player player;
	StateStack state_stack;
	TextureHolder textures;
	FontHolder fonts;
	MusicPlayer music;
	SoundPlayer sounds;
};