#include "Data.h"
#include "Aircraft.h"
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"

using namespace std::placeholders;

std::vector<AircraftData> initializeAircraftData()
{
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::Eagle].hitpoints = 250;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].fireInterval = sf::seconds(1);
	data[Aircraft::Eagle].texture = Textures::Eagle;

	data[Aircraft::Raptor].hitpoints = 100;
	data[Aircraft::Raptor].speed = 80.f;
	data[Aircraft::Raptor].texture = Textures::Raptor;
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].fireInterval = sf::seconds(3);

	data[Aircraft::Avenger].hitpoints = 50;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].texture = Textures::Avenger;
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f)); 
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].fireInterval = sf::seconds(3);

	data[Aircraft::Boss].hitpoints = 500;
	data[Aircraft::Boss].speed = 150.f;
	data[Aircraft::Boss].texture = Textures::Raptor;
	data[Aircraft::Boss].directions.push_back(Direction(90.f, 300.f));
	data[Aircraft::Boss].directions.push_back(Direction(-90.f, 300.f));
	data[Aircraft::Boss].directions.push_back(Direction(-90.f, 300.f));
	data[Aircraft::Boss].directions.push_back(Direction(90.f, 300.f));
	data[Aircraft::Boss].fireInterval = sf::seconds(2);

	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Bullets;

	data[Projectile::EnemyBullet].damage = 5;
	data[Projectile::EnemyBullet].speed = 250.f;
	data[Projectile::EnemyBullet].texture = Textures::Bullets;

	data[Projectile::Missile].damage = 50;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Textures::Missile;

	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].texture = Textures::Health;
	data[Pickup::HealthRefill].action = [](Aircraft& a) { if (a.getHitpoints() < 250.f) a.repair(25); };

	data[Pickup::MissileRefill].texture = Textures::MissilePick;
	data[Pickup::MissileRefill].action = std::bind(&Aircraft::collectMissiles, _1, 3);

	data[Pickup::FireSpread].texture = Textures::FireSpread;
	data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseSpread, _1);

	data[Pickup::FireRate].texture = Textures::FireRate;
	data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, _1);

	return data;
}

std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	data[Particle::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Propellant].lifetime = sf::seconds(0.8f);

	data[Particle::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Smoke].lifetime = sf::seconds(4.f);


	return data;
}