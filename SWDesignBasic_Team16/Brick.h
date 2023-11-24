#pragma once
#include "RangedWeapon.h"
class Brick : public RangedWeapon
{
private:
public:
	Brick(float cooltime, float damage, float duration, sf::Vector2f position, float speed);
	~Brick();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection);
	void render(sf::RenderTarget* target);
};
