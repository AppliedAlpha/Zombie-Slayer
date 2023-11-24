#pragma once

#include "stdafx.h"
#include "AoE.h"

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
	int hitCount;
	int maxHitCount;
	bool explosion;

	Bullet(sf::RectangleShape& shape, sf::Vector2f direction, float speed, float duration, int maxHitCount, bool explosion);
	~Bullet();
	void update(const float& dt, float cx, float cy);
	void render(sf::RenderTarget* target);
	void move();
	AoE* explode(float radius, float duration, float damage, sf::Vector2f position);
};

