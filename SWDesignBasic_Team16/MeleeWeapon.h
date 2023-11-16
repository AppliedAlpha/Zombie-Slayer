#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:

protected:
public:
	MeleeWeapon(float cooltime, float damage, float duration);
	~MeleeWeapon();
	sf::RectangleShape shape;

	virtual void initShape();

};