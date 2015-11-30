#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ObjectCategory.h"
struct Command;
struct SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{

	typedef std::unique_ptr<SceneNode> ptr;

	SceneNode();

	void attachChild(ptr child);
	ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);
	 
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getCategory();
	void callCommand(const Command& command, sf::Time dt);

	std::vector<ptr> children;
	SceneNode* parent;
};
