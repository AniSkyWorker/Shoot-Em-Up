#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

struct SceneNode : public sf::Transformable
{
	typedef std::unique_ptr<SceneNode> ptr;

	SceneNode();
	std::vector<ptr> children;
	SceneNode* parent;

	void attachChild(ptr child);
	ptr detachChild(const SceneNode& node);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(sf::Time dt);
	void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
};

