#pragma once
#define _USE_MATH_DEFINES

#include <SFML\Graphics.hpp>

struct SceneNode;

struct Math
{
	Math() = delete;

	static sf::Vector2f cartesian(float radius, float angle_degrees);

	static float sign(bool value);
	static int random(int max);

	static float to_radian(float angle);
	static float to_degree(float angle);
	static float distance(sf::Vector2f& lhs, sf::Vector2f& rhs);

	static sf::Vector2f normalized(sf::Vector2f vec);

	static float polarAngle(sf::Vector2f vec);
};