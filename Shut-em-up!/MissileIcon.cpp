#include "MissileIcon.h"
#include "ResourceHolder.h"


MissileIcon::MissileIcon(const TextureHolder& textures)
	:sprite(textures.get(Textures::MissilePick))
{
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().width / 2.f);
	sprite.setScale(0.5f, 0.5);
}

void MissileIcon::setReady(sf::Time dt)
{
	if (dt > sf::Time::Zero)
		sprite.setColor(sf::Color(255, 255, 255, 255 - dt.asMilliseconds() *0.2));
	else
		sprite.setColor(sf::Color(255, 255, 255, 255));
}

void MissileIcon::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

