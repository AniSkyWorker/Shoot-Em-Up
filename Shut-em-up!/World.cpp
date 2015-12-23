#include "World.h"
#include "Projectile.h"
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <memory>
#include <iostream>

World::World(sf::RenderWindow& window, FontHolder& fonts) 
	:world_window(window)
	,world_view(window.getDefaultView())
	,textures()
	,scene_graph()
	,enemies()
	,scene_layers()
	,world_bounds(0.f , 0.f, world_view.getSize().x , 2000.f)
	,player_position(world_view.getSize().x / 2, world_bounds.height - (world_view.getSize().y / 2))
	,scroll_speed(-50)
	,player_aircraft(nullptr)
	,fonts(fonts)
	,spawn_points()
{
	loadTextures();
	buildScene();

	world_view.setCenter(player_position);
}

void World::update(sf::Time dt)
{
	if (world_bounds.top - getBattlefieldBounds().top <= 50)
		world_view.move(0.f, scroll_speed * dt.asSeconds());
	else
		scroll_speed = 0;

	player_aircraft->setVelocity(0.f, 0.f);

	destroyEntitiesOutsideView();

	guideMissiles();

	while (!command_queue.isEmpty())
		scene_graph.callCommand(command_queue.pop(), dt);

	updatePlayerVelocity();

	handleCollisions();
	scene_graph.removeWrecks();

	spawnEnemies();
	scene_graph.update(dt, command_queue);

	updatePlayerPosition();
}

void World::updatePlayerPosition()
{
	sf::FloatRect view_bounds(world_view.getCenter() - world_view.getSize() / 2.f, world_view.getSize());
	float border_distance = 40.f;
	sf::Vector2f position = player_aircraft->getPosition();

	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);

	player_aircraft->setPosition(position);
}

void World::updatePlayerVelocity()
{
	sf::Vector2f velocity = player_aircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		player_aircraft->setVelocity(velocity / std::sqrt(2.f));
	player_aircraft->accelerate(0.f, scroll_speed);
}

void World::draw()
{
	world_window.setView(world_view);
	world_window.draw(scene_graph);
}

void World::loadTextures()
{
	textures.load(Textures::Eagle, "Media/textures/Eagle.png");
	textures.load(Textures::Raptor, "Media/textures/Raptor.png");
	textures.load(Textures::Avenger, "Media/textures/Avenger.png");
	textures.load(Textures::Desert, "Media/textures/Desert.png");
	textures.load(Textures::Bullets, "Media/textures/Bullet.png");
	textures.load(Textures::Missile, "Media/textures/Missile.png");

	textures.load(Textures::Health, "Media/Textures/HealthRefill.png");
	textures.load(Textures::MissilePick, "Media/Textures/MissileRefill.png");
	textures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
	textures.load(Textures::FireRate, "Media/Textures/FireRate.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i < count; ++i)
	{
		Category::Type category = (i == aircraft) ? Category::SceneAirLayer : Category::None;
		SceneNode::Ptr layer(new SceneNode(category));
		scene_layers[i] = layer.get();

		scene_graph.attachChild(std::move(layer));
	}

	sf::Texture& texture = textures.get(Textures::Desert);
	sf::IntRect texture_rect(world_bounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, texture_rect));
	background_sprite->setPosition(world_bounds.left, world_bounds.top);
	scene_layers[background]->attachChild(std::move(background_sprite));

	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, textures, fonts)); 
	player_aircraft = player.get();
	player_aircraft ->setPosition(player_position);
	scene_layers[aircraft]->attachChild(std::move(player));

	addEnemies();
}

CommandQueue& World::getCommandQueue()
{
	return command_queue;
}

sf::FloatRect World::getViewBounds()
{
	return sf::FloatRect(world_view.getCenter() - world_view.getSize() / 2.f, world_view.getSize());
}

sf::FloatRect World::getBattlefieldBounds()
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 50.f;
	bounds.height += 50.f;
	return bounds;
}

void World::spawnEnemies()
{
	while (!spawn_points.empty() && spawn_points.back().y > getBattlefieldBounds().top)
	{
		SpawnPoint spawn = spawn_points.back();
		std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, textures, fonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);
		
		scene_layers[aircraft]->attachChild(std::move(enemy));
		spawn_points.pop_back();
	}
}
void World::addEnemy(Aircraft::Type type, float x, float y)
{
	SpawnPoint spawn(type, player_position.x + x, player_position.y - y);
	spawn_points.push_back(spawn);
}

void World::addEnemies()
{
	addEnemy(Aircraft::Avenger, 0.f, 500.f);
	addEnemy(Aircraft::Avenger, -40.f, 700.f);
	addEnemy(Aircraft::Raptor, 100.f, 800.f);
	addEnemy(Aircraft::Avenger, 0.f, 1000.f);
	addEnemy(Aircraft::Raptor, +200.f, 1500.f);
	addEnemy(Aircraft::Avenger, 0.f, 1500.f);
	addEnemy(Aircraft::Raptor, -200.f, 1500.f);
	addEnemy(Aircraft::Raptor, -70.f, 1700.f);
	addEnemy(Aircraft::Raptor, -70.f, 1700.f);
	addEnemy(Aircraft::Raptor, 250.f, 1800.f);
	addEnemy(Aircraft::Raptor, 70.f, 1800.f);
	addEnemy(Aircraft::Boss, 0.f, 1700.f);
	std::sort(spawn_points.begin(), spawn_points.end(), [](SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});

}

void World::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
		{
			e.destroy();
		}
	});

	command_queue.push(command);
}

void World::guideMissiles()
{
	Command collector;
	collector.category = Category::EnemyAircraft;
	collector.action = derivedAction<Aircraft>([this] (Aircraft& enemy, sf::Time)
	{
		if (!enemy.isDestroyed())
			enemies.push_back(&enemy);
	});

	Command missile_guider;
	missile_guider.category = Category::AlliedProjectile;
	missile_guider.action = derivedAction<Projectile>([this] (Projectile& missile, sf::Time)
	{
		if (!missile.isGuided())
			return;
		float min_dist = std::numeric_limits<float>::max();
		Aircraft* closest_enemy = nullptr;

		for(Aircraft* enemy : enemies)
		{
			float enemy_dist = Math::distance(missile.getWorldPosition(), enemy->getWorldPosition());

			if (enemy_dist < min_dist)
			{
				closest_enemy = enemy;
				min_dist = enemy_dist;
			}
		}

		if (closest_enemy)
		{
			missile.guideTowards(closest_enemy->getWorldPosition());
		}
	});

	command_queue.push(collector);
	command_queue.push(missile_guider);
	enemies.clear();
}

bool World::matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}
void World::handleCollisions()
{
	std::set<SceneNode::Pair> collision_pairs_set;
	scene_graph.checkSceneCollision(scene_graph, collision_pairs_set);

	for(SceneNode::Pair pair : collision_pairs_set)
	{
		if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& enemy = static_cast<Aircraft&>(*pair.second);

			player.damage(enemy.getHitpoints());
			enemy.destroy();
		}

		 if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			pickup.apply(player);
			pickup.destroy();
		}

		else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
			|| matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		{
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}
	}
}

bool World::hasPlayerReachedEnd()
{
	return world_bounds.top >= player_aircraft->getBoundingRect().top - 10.f && enemies.empty();
}

bool World::hasPlayerAlive()
{
	return !player_aircraft->isMarkedForRemoval();
}