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
	float slowRate;
	bool mobTarget;
	bool disappear;
	AoE(float radius, float duration, float damage, sf::Vector2f position);
	AoE(float radius, float duration, sf::Vector2f position, float slowRate);
	AoE(float radius, float duration, float damage, sf::Vector2f position, bool mobTraget);
	~AoE();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

