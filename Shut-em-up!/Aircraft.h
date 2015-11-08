#include "Entity.h"
#include "ResourceIdientificators.h"
#include "ResourceHolder.h"
struct Aircraft {
	enum Type
	{
		Eagle,
		Raptor,
	};

	Aircraft(Type type, const TextureHolder& textures);

	
	Type Airtype;
	sf::Sprite sprite;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

