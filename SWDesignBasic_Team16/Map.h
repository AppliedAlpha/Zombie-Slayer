#pragma once

#include "stdafx.h"

class Map
{
private:
	sf::Vertex background[4];

public:
	Map();
	virtual ~Map();

	void update();
	void render(sf::RenderTarget* target);

};

