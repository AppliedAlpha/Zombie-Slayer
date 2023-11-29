#pragma once
#include "MeleeWeapon.h"
class Spear : public MeleeWeapon
{
private:
public:
	Spear(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color);
	~Spear();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	void render(sf::RenderTarget* target);
	void levelUp();
};

