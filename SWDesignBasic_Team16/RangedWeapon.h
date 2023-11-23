#pragma once

#include "Weapon.h"
#include "Bullet.h"
#include "stdafx.h"

class RangedWeapon : public Weapon
{
private:

protected:
public:
	RangedWeapon(float cooltime, float damage, float duration, sf::Vector2f position, float speed);
	virtual ~RangedWeapon();
	float speed;
	sf::Vector2f activeDirection;
	std::deque<Bullet*> bullets;

	virtual void initShape();
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	virtual void render(sf::RenderTarget* target);
};
