#pragma once
#include "stdafx.h"
#include "Entity.h"

class Weapon
{
private:
protected:
public:
	int count;
	int level;
	int maxLevel;
	float cooltime;
	float damage;
	float duration;
	bool active;
	sf::RectangleShape shape;
	Weapon(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color);
	virtual ~Weapon();
	virtual void initShape(sf::Color color);
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	virtual void render(sf::RenderTarget* target);
	virtual void levelUp();
	float getViewAngle(sf::Vector2f viewDirection);
};