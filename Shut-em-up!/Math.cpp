#include "Math.h"
#include <random>

sf::Vector2f Math::cartesian(float radius, float angle_degrees)
{
	angle_degrees += 90.f;
	return sf::Vector2f{ std::cos(to_radian(angle_degrees)), std::sin(to_radian(angle_degrees)) } * radius;
}

float Math::to_radian(float angle)
{
	return M_PI / 180.f * angle;
}

float Math::to_degree(float radian)
{
	return 180.f / M_PI * radian;
}

float Math::sign(bool value)
{
	return value ? -1.f : +1.f;
}

int Math::random(int max)
{
	auto seed = static_cast<unsigned long>(std::time(nullptr));
	auto engine = std::default_random_engine(seed);
	std::uniform_int_distribution<> distr(0, max - 1);
	return distr(engine);
}

float Math::distance(sf::Vector2f& lhs, sf::Vector2f& rhs)
{
	sf::Vector2f lenght = lhs - rhs;
	return std::sqrt(lenght.x * lenght.x + lenght.y * lenght.y);
}