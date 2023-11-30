#pragma once

#include "stdafx.h"

class Map
{
private:
	// sf::Vertex background[4];
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

public:
	Map();
	virtual ~Map();

	void update();
	void render(sf::RenderTarget* target);

};

