#pragma once
#include "ResourceIdientificators.h"
#include <vector>
#include "Aircraft.h"

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
	int hitpoints;
	float speed;
	Textures::ID texture;
	std::vector<Direction> directions;
};
std::vector<AircraftData> initAircraftData();
