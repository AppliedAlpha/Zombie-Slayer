#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:

protected:
public:
	MeleeWeapon(float cooltime, float damage, float duration);
	virtual ~MeleeWeapon();
	sf::RectangleShape shape;

	virtual void initShape();
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle);
	virtual void render(sf::RenderTarget* target);
};