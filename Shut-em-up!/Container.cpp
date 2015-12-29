#include "Container.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{
	Container::Container()
		:children()
		,selected_child(-1)
	{
	}

	void Container::pack(Component::Ptr component)
	{
		children.push_back(component);

		if (!hasSelection() && component->isSelectable())
			select(children.size() - 1);
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	void Container::handleEvent(const sf::Event& event)
	{
		if (hasSelection() && children[selected_child]->isActive())
		{
			children[selected_child]->handleEvent(event);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			{
				selectPrevious();
			}
			else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				selectNext();
			}
			else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				if (hasSelection())
					children[selected_child]->activate();
			}
		}
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for(const Component::Ptr& child : children)
			target.draw(*child, states);
	}

	bool Container::hasSelection() const
	{
		return selected_child >= 0;
	}

	void Container::select(std::size_t index)
	{
		if (children[index]->isSelectable())
		{
			if (hasSelection())
				children[selected_child]->deselect();

			children[index]->select();
			selected_child = index;
		}
	}

	void Container::selectNext()
	{
		if (!hasSelection())
			return;

		int next = selected_child;
		do
			next = (next + 1) % children.size();
		while (!children[next]->isSelectable());

		select(next);
	}

	void Container::selectPrevious()
	{
		if (!hasSelection())
			return;

		int prev = selected_child;
		do
			prev = (prev + children.size() - 1) % children.size();
		while (!children[prev]->isSelectable());

		select(prev);
	}

}
