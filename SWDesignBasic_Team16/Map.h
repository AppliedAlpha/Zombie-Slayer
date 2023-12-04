#pragma once

#include "stdafx.h"

class Map
{
private:
	// sf::Vertex background[4];
	sf::Texture bgTexture[5];
	sf::Sprite bgSprite;

public:
	Map();
	virtual ~Map();

	void update();
	void changeSpriteByStage(int stage);
	void render(sf::RenderTarget* target);

};

