#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Command.h"

SceneNode::SceneNode() : parent(nullptr), children()
{
}

void SceneNode::attachChild(ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}
SceneNode::ptr SceneNode::detachChild(const SceneNode& node) {
	auto found = std::find_if(children.begin(), children.end(), [&](ptr& p) -> bool { return p.get() == &node; });
	assert(found != children.end());

	ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *=  getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Do nothing by default
}
void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each(const ptr& child in children)
		child->draw(target, states);
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}
void SceneNode::updateCurrent(sf::Time dt)
{
	//
}
void SceneNode::updateChildren(sf::Time dt)
{
	for each(const ptr& child in children)
		child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		transform *= node->getTransform();
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory()
{
	return Category::scene;
}

void SceneNode::callCommand(const Command& command, sf::Time dt)
{
	if (command.category& getCategory())
		command.action(*this, dt);
	for each(const ptr& child in children)
		child->callCommand(command, dt);
}