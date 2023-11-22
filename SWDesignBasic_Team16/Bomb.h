#pragma once
#include "AoeItem.h"

class Bomb : public AoeItem
{
public:
	Bomb(float cooltime, float damage, float duration);
	~Bomb();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerPos, float cx, float cy);
	void render(sf::RenderTarget* target);
};