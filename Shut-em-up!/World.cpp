#include "World.h"
#include <SFML/Graphics/RenderWindow.hpp>
World::World(sf::RenderWindow& window) 
:world_window(window)
,world_view(window.getDefaultView())
,textures()
,SceneGraph()
,scene_layers()
,world_bounds(0.f , 0.f, world_view.getSize().x , 2000.f)
,player_position(world_view.getSize().x / 2, world_bounds.height - (world_view.getSize().y / 2))
,scroll_speed(-50)
,player_aircraft(nullptr)
{
	loadTextures();
	buildScene();

	world_view.setCenter(player_position);
}

void World::update(sf::Time dt)
{
	world_view.move(0, scroll_speed * dt.asSeconds());
	sf::Vector2f position = player_aircraft->getPosition();
	sf::Vector2f velocity = player_aircraft->getVelocity();
	velocity.y = 0;
	velocity.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)))
		velocity.x = -40;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
		velocity.x = 40;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)))
		velocity.y = -80;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)))
		velocity.y = 80;
	/*if (position.x <= world_bounds.left + 150 || position.x >= world_bounds.left + world_bounds.width - 150)
	{
		printf("%d", 1);
		velocity.x = -velocity.x;

	}*/
		
	player_aircraft->setVelocity(velocity);
		SceneGraph.update(dt);
}

void World::draw()
{
	world_window.setView(world_view);
	world_window.draw(SceneGraph);
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

		SceneGraph.attachChild(std::move(layer));
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