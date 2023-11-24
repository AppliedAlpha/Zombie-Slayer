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
	RangedWeapon(float cooltime, float damage, float duration, sf::Vector2f position, float speed, float radius, float explosionDamage, float explosionDuration);
	virtual ~RangedWeapon();
	float speed;
	sf::Vector2f activeDirection;
	std::vector<Bullet*> bullets;
	int maxHitCount;
	bool explosion;
	float radius;
	float explosionDamage;
	float explosionDuration;

	virtual void initShape();
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	virtual void render(sf::RenderTarget* target);
};
