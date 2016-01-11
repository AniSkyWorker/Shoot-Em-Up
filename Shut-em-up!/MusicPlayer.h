#pragma once
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"

#include <SFML/Audio.hpp>

struct MusicPlayer
{
	MusicPlayer();

	void play(Music::ID theme);
	void stop();

	void setPaused(bool paused);
	void setVolume(float volume);

	sf::Music music;
	std::map<Music::ID, std::string> file_names;
	float volume;
};

