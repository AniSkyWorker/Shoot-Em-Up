#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceIdientificators.h"
#include <vector>


struct Aircraft;

struct Direction
{
	Direction(float angle, float distance)
		: angle(angle)
		, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct AircraftData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	sf::Time						fireInterval;
	std::vector<Direction>			directions;
};

struct ProjectileData
{
	int								damage;
	float							speed;
	Textures::ID					texture;
};



std::vector<AircraftData>	initializeAircraftData();
std::vector<ProjectileData>	initializeProjectileData();