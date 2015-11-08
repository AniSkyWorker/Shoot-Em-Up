
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
		Space,
	};
}
template <typename Resource, typename Identifier> class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;