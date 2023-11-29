#pragma once
#include "MeleeWeapon.h"
class Sword : public MeleeWeapon
{
private:
public:
	Sword(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color);
	~Sword();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection);
	void render(sf::RenderTarget* target);
	void levelUp();
};