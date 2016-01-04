#pragma once
#include "ResourceIdientificators.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>


struct Aircraft;

struct Direction
{
	Direction(float angle, float distance)
		:angle(angle)
		,distance(distance)
	{
	}

	float angle;
	float distance;
};

struct AircraftData
{
	int	hitpoints;
	float speed;
	Textures::ID texture;
	sf::IntRect texture_rect;
	sf::Time fire_interval;
	sf::Time missile_interval;
	std::vector<Direction> directions;
	bool roll_animation;
};

struct ProjectileData
{
	int	damage;
	float speed;
	Textures::ID texture;
	sf::IntRect texture_rect;
};

struct PickupData
{
	std::function<void(Aircraft&)> action;
	Textures::ID texture;
};

struct ParticleData
{
	sf::Color						color;
	sf::Time						lifetime;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData>	initializeProjectileData();
std::vector<PickupData> initializePickupData();
std::vector<ParticleData> initializeParticleData();

