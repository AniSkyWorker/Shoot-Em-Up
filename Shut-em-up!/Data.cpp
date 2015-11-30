#include "Data.h"

std::vector<AircraftData> initAircraftData()
{
	std::vector<AircraftData> data(Aircraft::Count);
	data[Aircraft::Eagle].hitpoints = 100.f;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].texture = Textures::Eagle;


	data[Aircraft::Raptor].hitpoints = 50.f;
	data[Aircraft::Raptor].speed = 80.f;
	data[Aircraft::Raptor].texture = Textures::Raptor;
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 100.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 100.f));

	return data;
}