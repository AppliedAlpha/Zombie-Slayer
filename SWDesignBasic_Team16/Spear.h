#pragma once
#include "MeleeWeapon.h"
class Spear : public MeleeWeapon
{
private:
public:
	Spear(float cooltime, float damage, float duration);
	~Spear();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle);
	void render(sf::RenderTarget* target);
};

