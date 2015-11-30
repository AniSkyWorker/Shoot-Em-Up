#include "World.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <memory>
#include <iostream>
World::World(sf::RenderWindow& window, FontHolder& fonts) 
:world_window(window)
,world_view(window.getDefaultView())
,textures()
,scene_graph()
,scene_layers()
,world_bounds(0.f , 0.f, world_view.getSize().x , 5000.f)
,player_position(world_view.getSize().x / 2, world_bounds.height - (world_view.getSize().y / 2))
,scroll_speed(-50)
,player_aircraft(nullptr)
,fonts(fonts)
{
	loadTextures();
	buildScene();

	world_view.setCenter(player_position);
}

void World::update(sf::Time dt)
{
	world_view.move(0.f, scroll_speed * dt.asSeconds());
	player_aircraft->setVelocity(0.f, 0.f);

	while (!command_queue.isEmpty())
		scene_graph.callCommand(command_queue.pop(), dt);

	sf::Vector2f velocity = player_aircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		player_aircraft->setVelocity(velocity / std::sqrt(2.f));
	player_aircraft->setVelocity(player_aircraft->getVelocity() + sf::Vector2f{ 0.f, scroll_speed });

	spawnEnemies();
	scene_graph.update(dt);
	sf::FloatRect view_bounds(world_view.getCenter() - world_view.getSize() / 2.f, world_view.getSize());
	float border_distance = 40.f;
	sf::Vector2f position = player_aircraft->getPosition();

	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);

	player_aircraft->setPosition(position);
	
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
	textures.load(Textures::Desert, "Media/textures/Desert.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i < count; ++i)
	{
		SceneNode::ptr layer(new SceneNode());
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
	bounds.top -= 100.f;
	bounds.height += 100.f;
	return bounds;
}

void World::spawnEnemies()
{
	//std::cout << spawn_points.back().y << getBattlefieldBounds().top << std::endl;
	while (!spawn_points.empty())// && spawn_points.back().y > getBattlefieldBounds().top)
	{
		SpawnPoint spawn = spawn_points.back();
		std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, textures, fonts));
		printf("%d", 1);
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
	addEnemy(Aircraft::Raptor, 0.f, 500.f);
	addEnemy(Aircraft::Raptor, 0.f, 1000.f);
	addEnemy(Aircraft::Raptor, +100.f, 1150.f);
	addEnemy(Aircraft::Raptor, -100.f, 1150.f);
	addEnemy(Aircraft::Raptor, 70.f, 1500.f);
	addEnemy(Aircraft::Raptor, -70.f, 1500.f);
	addEnemy(Aircraft::Raptor, -70.f, 1710.f);
	addEnemy(Aircraft::Raptor, 70.f, 1700.f);
	addEnemy(Aircraft::Raptor, 30.f, 1850.f);
	addEnemy(Aircraft::Raptor, 300.f, 2200.f);
	addEnemy(Aircraft::Raptor, -300.f, 2200.f);
	addEnemy(Aircraft::Raptor, 0.f, 2200.f);
	addEnemy(Aircraft::Raptor, 0.f, 2500.f);
	addEnemy(Aircraft::Raptor, -300.f, 2700.f);
}