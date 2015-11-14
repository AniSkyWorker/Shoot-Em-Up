#include "Aircraft.h"
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;
	case Aircraft::Raptor:
		return Textures::Raptor;
	}
}
Aircraft::Aircraft(Type type, const TextureHolder& textures) : Airtype(type), sprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(sprite, states);
}