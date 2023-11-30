#pragma once
#include "AoeItem.h"
class Bomb : public AoeItem
{
private:
public:
	Bomb(float cooltime, float damage, float duration, sf::Vector2f position);
	~Bomb();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy);
	void render(sf::RenderTarget* target);
};
