#pragma once
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"
#include "SoundPlayer.h"

#include <SFML/Graphics.hpp>

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
	World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds);

	void update(sf::Time dt);
	void draw();
	void loadTextures();
	void buildScene();

	CommandQueue& getCommandQueue();

	enum Layer
	{
		background,
		lowerAircraft,
		upperAircraft,
		count,
	};

	sf::RenderWindow& world_window;
	sf::View world_view;

	TextureHolder textures;
	FontHolder& fonts;
	SoundPlayer& sounds;

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

	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
	void handleCollisions();

	bool hasPlayerAlive();
	bool hasPlayerReachedEnd();

	void updatePlayerPosition();
	void updatePlayerVelocity();

	std::vector<SpawnPoint> spawn_points;
	sf::FloatRect getViewBounds();
	sf::FloatRect getBattlefieldBounds();
};