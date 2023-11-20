#pragma once
#include "MeleeWeapon.h"
class Grinder : public MeleeWeapon
{
private:
public:
	int rotation;
	Grinder(float cooltime, float damage, float duration);
	~Grinder();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle);
	void render(sf::RenderTarget* target);
};

