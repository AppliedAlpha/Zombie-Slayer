#include "Map.h"

Map::Map()
{
	// background.resize(4);

	background[0] = sf::Vertex(sf::Vector2f(-1280.f, -720.f), sf::Color(255, 255, 255, 127));
	background[1] = sf::Vertex(sf::Vector2f(2560.f, -720.f), sf::Color(0, 255, 0, 127));
	background[2] = sf::Vertex(sf::Vector2f(2560.f, 1440.f), sf::Color(0, 0, 0, 127));
	background[3] = sf::Vertex(sf::Vector2f(-1280.f, 1440.f), sf::Color(0, 255, 0, 127));
}

Map::~Map()
{
}

void Map::update()
{
}

void Map::render(sf::RenderTarget* target)
{
	target->draw(background, 4, sf::Quads);
}
