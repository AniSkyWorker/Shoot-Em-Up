#include "SoundPlayer.h"


#include <cmath>


namespace
{
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer()
	:sound_buffers()
	,sounds()
{
	sound_buffers.load(SoundEffect::AlliedGunfire, "Media/Sound/AlliedGunfire.wav");
	sound_buffers.load(SoundEffect::EnemyGunfire, "Media/Sound/EnemyGunfire.wav");
	sound_buffers.load(SoundEffect::Explosion1, "Media/Sound/Explosion1.wav");
	sound_buffers.load(SoundEffect::Explosion2, "Media/Sound/Explosion2.wav");
	sound_buffers.load(SoundEffect::LaunchMissile, "Media/Sound/LaunchMissile.wav");
	sound_buffers.load(SoundEffect::CollectPickup, "Media/Sound/CollectPickup.wav");
	sound_buffers.load(SoundEffect::Button, "Media/Sound/Button.wav");

	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	play(effect, getListenerPosition());
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
	sounds.push_back(sf::Sound());
	sf::Sound& sound = sounds.back();

	sound.setBuffer(sound_buffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
	sounds.remove_if([](const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}
