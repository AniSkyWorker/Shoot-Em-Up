#include <SFML/Graphics.hpp>
#include "Aircraft.h"
#include "Entity.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include <array> 
struct World : sf::NonCopyable
{
	World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	void loadTextures();
	void buildScene();

	enum Layer
	{
		Background,
		Aircraft,
		count,
	};
	sf::RenderWindow& world_window;
	sf::View world_view;
	TextureHolder textures;
	SceneNode SceneGraph;
	std::array<SceneNode*, count> scene_layers;
	sf::FloatRect world_bounds;
	sf::Vector2f player_position;
	float scroll_speed;
	Aircraft* aircraft;
};

