#pragma once
#include "RangedWeapon.h"
class Rocket : public RangedWeapon
{
private:
public:
	Rocket(float cooltime, float damage, float duration, sf::Vector2f position, float speed, float radius, float explosionDamage, float explosionDuration);
	~Rocket();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection);
	void render(sf::RenderTarget* target);
};

