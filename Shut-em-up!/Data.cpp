#include "Data.h"
#include "Aircraft.h"
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"

using namespace std::placeholders;

std::vector<AircraftData> initializeAircraftData()
{
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::Eagle].hitpoints = 350;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].fire_interval = sf::seconds(0.2f);
	data[Aircraft::Eagle].missile_interval = sf::seconds(1);
	data[Aircraft::Eagle].texture = Textures::Eagle;
	data[Aircraft::Eagle].texture_rect = sf::IntRect(0, 0, 48, 64);
	data[Aircraft::Eagle].roll_animation = true;

	data[Aircraft::Raptor].hitpoints = 100;
	data[Aircraft::Raptor].speed = 80.f;
	data[Aircraft::Raptor].texture = Textures::Raptor;
	data[Aircraft::Raptor].texture_rect = sf::IntRect(0, 0, 84, 68);
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].missile_interval = sf::seconds(10);
	data[Aircraft::Raptor].fire_interval = sf::seconds(2);
	data[Aircraft::Raptor].roll_animation = true;

	data[Aircraft::Avenger].hitpoints = 50;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].texture = Textures::Avenger;
	data[Aircraft::Avenger].texture_rect = sf::IntRect(0, 0, 60, 59);
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f)); 
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].fire_interval = sf::seconds(1);
	data[Aircraft::Avenger].roll_animation = false;
	data[Aircraft::Avenger].missile_interval = sf::Time::Zero;

	data[Aircraft::Boss].hitpoints = 1000;
	data[Aircraft::Boss].speed = 100.f;
	data[Aircraft::Boss].texture = Textures::Raptor;
	data[Aircraft::Boss].texture_rect = sf::IntRect(0, 0, 84, 68);
	data[Aircraft::Boss].directions.push_back(Direction(+90.f, 200.f));
	data[Aircraft::Boss].directions.push_back(Direction(0.f, 200.f));
	data[Aircraft::Boss].directions.push_back(Direction(-135.f, 282.f));
	data[Aircraft::Boss].directions.push_back(Direction(-90.f, 200.f));
	data[Aircraft::Boss].directions.push_back(Direction(0.f, 200.f));
	data[Aircraft::Boss].directions.push_back(Direction(+135.f, 282.f));
	data[Aircraft::Boss].directions.push_back(Direction(0.f, 200.f));
	data[Aircraft::Boss].directions.push_back(Direction(+180.f, 200.f));
	data[Aircraft::Boss].fire_interval = sf::seconds(2);
	data[Aircraft::Boss].roll_animation = false;
	data[Aircraft::Boss].missile_interval = sf::seconds(2);

	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 8;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Bullets;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 250.f;
	data[Projectile::EnemyBullet].texture = Textures::Bullets;

	data[Projectile::AlliedMissile].damage = 50;
	data[Projectile::AlliedMissile].speed = 150.f;
	data[Projectile::AlliedMissile].texture = Textures::Missile;

	data[Projectile::EnemyMissile].damage = 30;
	data[Projectile::EnemyMissile].speed = 150.f;
	data[Projectile::EnemyMissile].texture = Textures::Missile;

	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].texture = Textures::Health;
	data[Pickup::HealthRefill].texture_rect = sf::IntRect(0, 0, 40, 40);
	data[Pickup::HealthRefill].action = [](Aircraft& a) { if (a.getHitpoints() < 250.f) a.repair(25); };

	data[Pickup::MissileRefill].texture = Textures::MissilePick;
	data[Pickup::MissileRefill].texture_rect = sf::IntRect(0, 0, 40, 40);
	data[Pickup::MissileRefill].action = std::bind(&Aircraft::collectMissiles, _1, 3);

	data[Pickup::FireSpread].texture = Textures::FireSpread;
	data[Pickup::FireSpread].texture_rect = sf::IntRect(0, 0, 40, 40);
	data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseSpread, _1);

	data[Pickup::FireRate].texture = Textures::FireRate;
	data[Pickup::FireRate].texture_rect = sf::IntRect(0, 0, 40, 40);
	data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, _1);

	return data;
}

std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	data[Particle::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Propellant].lifetime = sf::seconds(0.8f);

	data[Particle::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Smoke].lifetime = sf::seconds(5.f);

	data[Particle::EnemySmoke].color = sf::Color::Red;
	data[Particle::EnemySmoke].lifetime = sf::seconds(2.f);

	data[Particle::Tracing].color = sf::Color(255, 255, 255);
	data[Particle::Tracing].lifetime = sf::seconds(2.f);

	return data;
}