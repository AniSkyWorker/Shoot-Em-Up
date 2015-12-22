#pragma once

#include <vector>
#include <memory>
#include <set>
#include <SFML/Graphics.hpp>
#include "ObjectCategory.h"

struct Command;
struct CommandQueue;

struct SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	SceneNode(Category::Type category = Category::None);

	void attachChild(Ptr child);
	Ptr	detachChild(const SceneNode& node);

	void update(sf::Time dt, CommandQueue& commands);

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	void callCommand(const Command& command, sf::Time dt);
	virtual unsigned int getCategory() const;

	void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void removeWrecks();
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;

	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	void updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Ptr> children;
	SceneNode* parent;
	Category::Type default_category;
};

float distance(const SceneNode& lhs, const SceneNode& rhs);
bool collision(const SceneNode& lhs, const SceneNode& rhs);