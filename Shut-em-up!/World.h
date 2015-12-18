#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include "Command.h"

#include <array>

namespace sf
{
	class RenderWindow;
}

struct World : private sf::NonCopyable
{
	explicit World(sf::RenderWindow& window, FontHolder& fonts);

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
	FontHolder& fonts;
	SceneNode scene_graph;
	std::array<SceneNode*, count> scene_layers;
	sf::FloatRect world_bounds;
	sf::Vector2f player_position;
	float scroll_speed;
	Aircraft* player_aircraft;
	std::vector<Aircraft*>	enemies;
	CommandQueue command_queue;

	struct SpawnPoint
	{
		SpawnPoint(Aircraft::Type type, float x, float y)
		:type(type)
		,x(x)
		,y(y)
		{
		}

		Aircraft::Type type;
		float x;
		float y;
	};

	void spawnEnemies();
	void addEnemies();
	void addEnemy(Aircraft::Type type, float x, float y);
	void destroyEntitiesOutsideView();

	void guideMissiles();

	std::vector<SpawnPoint> spawn_points;
	sf::FloatRect getViewBounds();
	sf::FloatRect getBattlefieldBounds();
};