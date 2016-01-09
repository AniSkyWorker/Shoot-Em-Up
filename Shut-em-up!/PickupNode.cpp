#include "PickupNode.h"
#include "ResourceHolder.h"
#include "Data.h"

namespace
{
	const std::vector<PickupData> Table = initializePickupData();
}

PickupNode::PickupNode(const TextureHolder& textures)
	:spread_sprite(textures.get(Textures::FireSpread), Table[Pickup::FireSpread].texture_rect)
	,rate_sprite(textures.get(Textures::FireRate), Table[Pickup::FireRate].texture_rect)
{
	spread_sprite.setOrigin(spread_sprite.getGlobalBounds().width / 2.f, spread_sprite.getGlobalBounds().width / 2.f);
	rate_sprite.setOrigin(rate_sprite.getGlobalBounds().width / 2.f, rate_sprite.getGlobalBounds().width / 2.f);
	rate_sprite.setPosition(spread_sprite.getPosition().x + 20.f, spread_sprite.getPosition().y);
	spread_sprite.setScale(0.5f, 0.5);
	rate_sprite.setScale(0.5f, 0.5);
}

void PickupNode::checkPickup(int spread_lvl, int fire_rate)
{
	sf::IntRect spread_texture_rect = Table[Pickup::FireSpread].texture_rect;
	switch (spread_lvl)
	{
	case 2:
		spread_texture_rect.left += spread_texture_rect.width;
		spread_sprite.setTextureRect(spread_texture_rect);
		break;
	case 3:
		spread_texture_rect.left += spread_texture_rect.width * 2;
		spread_sprite.setTextureRect(spread_texture_rect);
		break;
	}

	sf::IntRect rate_texture_rect = Table[Pickup::FireSpread].texture_rect;
	switch (fire_rate)
	{
	case 0:
		rate_sprite.setColor(sf::Color(255, 255, 255, 0));
		break;
	case 1:
		rate_sprite.setColor(sf::Color(255, 255, 255, 255));
		break;
	case 2:
		rate_texture_rect.left += rate_texture_rect.width;
		rate_sprite.setTextureRect(rate_texture_rect);
		break;
	case 3:
		rate_texture_rect.left += rate_texture_rect.width * 2;
		rate_sprite.setTextureRect(rate_texture_rect);
		break;
	}

}

void PickupNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spread_sprite, states);
	target.draw(rate_sprite, states);
}