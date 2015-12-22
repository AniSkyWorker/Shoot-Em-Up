#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Avenger,
		Bullets,
		Missile,
		Desert,
		TitleScreen,
		Health,
		MissilePick,
		FireRate,
		FireSpread
	};
}

namespace Fonts 
{
	enum ID
	{
		Main,
	};
}

template <typename Resource, typename Identifier> struct ResourceHolder;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;