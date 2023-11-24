#pragma once

#include "stdafx.h"

class AoE
{
private:
public:
	sf::CircleShape shape;
	float duration;
	float count;
	float damage;
	bool disappear;
	AoE(float radius, float duration, float damage, sf::Vector2f position);
	~AoE();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

