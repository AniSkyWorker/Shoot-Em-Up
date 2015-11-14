#pragma once
namespace sf
{
	class Texture;
}
namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
	};
}
template <typename Resource, typename Identifier>
struct ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
