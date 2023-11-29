#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:

protected:
public:
	MeleeWeapon(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color);
	virtual ~MeleeWeapon();

	virtual void initShape();
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	virtual void render(sf::RenderTarget* target);
	virtual void levelUp();
};