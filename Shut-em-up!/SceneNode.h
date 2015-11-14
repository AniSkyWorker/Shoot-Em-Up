#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

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


	std::vector<ptr> children;
	SceneNode* parent;
	
};
