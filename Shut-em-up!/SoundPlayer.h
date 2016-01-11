#pragma once
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"

#include <SFML/Audio.hpp>
#include <list>

struct SoundPlayer
{
	SoundPlayer();

	void play(SoundEffect::ID effect);
	void play(SoundEffect::ID effect, sf::Vector2f position);

	void removeStoppedSounds();
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;


	SoundBufferHolder sound_buffers;
	std::list<sf::Sound> sounds;
};

