#pragma once

#include "stdafx.h"

class Bullet
{
private:
public:
	sf::RectangleShape shape;
	float speed;
	sf::Vector2f direction;
	float duration;
	float count;
	bool out;

	Bullet(sf::RectangleShape& shape, sf::Vector2f direction, float speed, float duration);
	~Bullet();
	void update(const float& dt, float cx, float cy);
	void render(sf::RenderTarget* target);
	void move();
};

