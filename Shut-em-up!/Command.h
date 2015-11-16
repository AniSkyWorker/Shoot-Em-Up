#pragma once
#include <functional>
#include "SceneNode.h"
#include <cassert>


struct Command
{
	Command()
		: action()
		, category(Category::none)
	{
	}

	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function <void(SceneNode&, sf::Time)> derivedAction(Function func)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		func(static_cast<GameObject&>(node), dt);
	};
}