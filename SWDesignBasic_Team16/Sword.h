#pragma once
#include "MeleeWeapon.h"
class Sword : public MeleeWeapon
{
private:
public:
	Sword(float cooltime, float damage, float duration, sf::Vector2f position);
	~Sword();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, float angle);
	void render(sf::RenderTarget* target);
};