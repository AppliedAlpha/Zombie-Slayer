#include "Map.h"

Map::Map()
{
	for (int i = 0; i < 5; i++)
		bgTexture[i].loadFromFile("./Resources/BG" + std::to_string(i+1) + ".jpg");

	// bgSprite.setTextureRect(sf::IntRect(-1280, -720, 3840, 2160));
	bgSprite.setTexture(bgTexture[0]);
	bgSprite.move(-1280, -720);
}

Map::~Map()
{
}

void Map::update()
{
}

void Map::changeSpriteByStage(int stage) {
	bgSprite.setTexture(bgTexture[stage - 1]);
}

void Map::render(sf::RenderTarget* target)
{
	target->draw(bgSprite);
}
