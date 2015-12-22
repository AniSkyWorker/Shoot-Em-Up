#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Command.h"
#include <iostream>

SceneNode::SceneNode(Category::Type category)
	:children()
	,parent(nullptr)
	,default_category(category)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(children.begin(), children.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != children.end());

	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time, CommandQueue&)
{
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
	for (Ptr& child : children)
		child->update(dt, commands);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);

//	drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : children)
		child->draw(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::callCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);
	for (const Ptr& child : children)
		child->callCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return default_category;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

float distance(const SceneNode& lhs, const SceneNode& rhs)
{
	sf::Vector2f lenght = lhs.getWorldPosition() - rhs.getWorldPosition();
	return std::sqrt(lenght.x * lenght.x + lenght.y * lenght.y);
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);
	
	for (Ptr& child : sceneGraph.children)
		checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	if (getCategory() & Category::EnemyProjectile)
		return;
	for(Ptr& child : children)
		child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::removeWrecks()
{
	auto wreckfieldBegin = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	children.erase(wreckfieldBegin, children.end());

	std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::removeWrecks));
}

bool SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	return false;
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}