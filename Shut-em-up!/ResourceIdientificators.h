#pragma once

namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Avenger,
		Boss,

		Bullets,
		Missile,

		MissionMap,

		TitleScreen,

		Health,
		Particle,
		MissilePick,
		FireRate,
		FireSpread,

		Explosion,
		Flame,
		Smoke,

		ButtonNormal,
		ButtonPressed,
		ButtonSelected
	};
}

namespace Fonts 
{
	enum ID
	{
		Main,
	};
}

namespace SoundEffect
{
	enum ID
	{
		AlliedGunfire,
		EnemyGunfire,
		Explosion1,
		Explosion2,
		LaunchMissile,
		CollectPickup,
		Button,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		MissionTheme,
	};
}

template <typename Resource, typename Identifier> struct ResourceHolder;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;