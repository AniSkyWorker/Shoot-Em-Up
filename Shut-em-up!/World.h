#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"
#include "Aircraft.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include <array> 
#include "CommandQueue.h"
namespace sf
{
	class RenderWindow;
}
struct World : sf::NonCopyable
{
	World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	void loadTextures();
	void buildScene();
	CommandQueue& getCommandQueue();

	enum Layer
	{
		background,
		aircraft,
		count,
	};

	sf::RenderWindow& world_window;
	sf::View world_view;
	TextureHolder textures;
	SceneNode scene_graph;
	std::array<SceneNode*, count> scene_layers;
	sf::FloatRect world_bounds;
	sf::Vector2f player_position;
	float scroll_speed;
	Aircraft* player_aircraft;
	CommandQueue command_queue;
};

//залить книжку в группу