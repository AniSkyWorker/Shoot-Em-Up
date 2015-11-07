#include "SceneNode.h"
#include <algorithm>
#include <cassert>


void SceneNode::attachChild(ptr child)
{
	children.emplace_back(std::move(child->parent = this));
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
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Do nothing by default
}
void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (const ptr& child in children)
	{
		child->draw(target, states);
	}
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}
void SceneNode::updateCurrent(sf::Time dt)
{

}
void SceneNode::updateChildren(sf::Time dt)
{
	for each(ptr& child in children)
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