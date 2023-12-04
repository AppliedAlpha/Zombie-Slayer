#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// #include "Random.h"

class CustomMath
{
public:
	static float getLength(const sf::Vector2f& vector);
	static sf::Vector2f normalize(const sf::Vector2f& vector);
	
	static std::pair<float, float> getRandomCoordWithRadius(const float& r);

	static int getMaxXp(const int level);
};

