#include "Map.h"

Map::Map()
{
	/*
	background[0] = sf::Vertex(sf::Vector2f(-1280.f, -720.f), sf::Color(255, 255, 255, 127));
	background[1] = sf::Vertex(sf::Vector2f(2560.f, -720.f), sf::Color(0, 255, 0, 127));
	background[2] = sf::Vertex(sf::Vector2f(2560.f, 1440.f), sf::Color(0, 0, 0, 127));
	background[3] = sf::Vertex(sf::Vector2f(-1280.f, 1440.f), sf::Color(0, 255, 0, 127));
	*/
	bgTexture.loadFromFile("./Resources/Moon.jpg");

	// bgSprite.setTextureRect(sf::IntRect(-1280, -720, 3840, 2160));
	bgSprite.setTexture(bgTexture);
	bgSprite.move(-1280, -720);
}

Map::~Map()
{
}

void Map::update()
{
}

void Map::render(sf::RenderTarget* target)
{
	// target->draw(background, 4, sf::Quads);
	target->draw(bgSprite);

	// 고속도로
}
