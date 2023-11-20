#pragma once
#include "stdafx.h"
#include "Entity.h"

class Weapon
{
private:
protected:
public:
	int count;
	float cooltime;
	float damage;
	float duration;
	bool active;
	sf::RectangleShape shape;
	Weapon(float cooltime, float damage, float duration);
	~Weapon();
	virtual void initShape();
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle);
	virtual void render(sf::RenderTarget* target);
};