#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class CustomMath
{
public:
	static float getLength(const sf::Vector2f& vector);
	static sf::Vector2f normalize(const sf::Vector2f& vector);

	static int getMaxXp(const int level);
};

