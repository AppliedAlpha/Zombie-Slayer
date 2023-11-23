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
	Weapon(float cooltime, float damage, float duration, sf::Vector2f position);
	virtual ~Weapon();
	virtual void initShape();
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	virtual void render(sf::RenderTarget* target);
	float getViewAngle(sf::Vector2f viewDirection);
};