#include "Aircraft.h"
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"
#include "Data.h"

namespace
{
	const std::vector<AircraftData> Table = initAircraftData();
}
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
Aircraft::Aircraft(Type type, const TextureHolder& textures,const FontHolder& fonts)
:Airtype(type)
,sprite(textures.get(Table[type].texture))
,Entity(Table[type].hitpoints)
,travelled_dist(0.f)
,direction_index(0)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	health_display = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	update();
}
void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(sprite, states);
}

unsigned int Aircraft::getCategory()
{
	switch (Airtype)
	{
	case Eagle:
		return Category::player_aircraft;
	default:
		return Category::enemy_aircraft;
	}
}

void Aircraft::update()
{
	health_display->setString(std::to_string(getHitpoints()));
	health_display->setPosition(0, 50);
	health_display->setRotation(-getRotation());
}

void Aircraft::updateMovement(sf::Time dt)
{
	const std::vector<Direction>& directions = Table[Airtype].directions;
	if (!directions.empty())
	{
		float dist_to_move = directions[direction_index].distance;
		if (travelled_dist > dist_to_move)
		{
			direction_index = (direction_index + 1) % directions.size();
			travelled_dist = 0.f;
		}
		float angle = directions[direction_index].angle + 90.f;
		float vx = Table[Airtype].speed * std::cos(angle * 3.14 / 180);
		float vy = Table[Airtype].speed * std::sin(angle * 3.14 / 180);
		setVelocity(vx, vy);
		travelled_dist += Table[Airtype].speed * dt.asSeconds();
	}
}

void Aircraft::updateCurrent(sf::Time dt)
{
	update();
	updateMovement(dt);
	Entity::updateCurrent(dt);
}