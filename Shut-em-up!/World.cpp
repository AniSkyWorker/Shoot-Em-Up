#include "World.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
World::World(sf::RenderWindow& window) 
:world_window(window)
,world_view(window.getDefaultView())
,textures()
,scene_graph()
,scene_layers()
,world_bounds(0.f , 0.f, world_view.getSize().x , 6000.f)
,player_position(world_view.getSize().x / 2, world_bounds.height - (world_view.getSize().y / 2))
,scroll_speed(-50)
,player_aircraft(nullptr)
,command_queue()
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
	printf("%d", 1);
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

	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, textures)); 
	player_aircraft = player.get();
	player_aircraft ->setPosition(player_position);
	scene_layers[aircraft]->attachChild(std::move(player));

	std::unique_ptr<Aircraft> left_plane(new Aircraft(Aircraft::Raptor, textures));
	left_plane->setPosition(-80.f, 50.f);
	player_aircraft->attachChild(std::move(left_plane));

	std::unique_ptr<Aircraft> right_plane(new Aircraft(Aircraft::Raptor, textures));
	right_plane->setPosition(80.f, 50.f);
	player_aircraft->attachChild(std::move(right_plane));
}

CommandQueue& World::getCommandQueue()
{
	return command_queue;
}