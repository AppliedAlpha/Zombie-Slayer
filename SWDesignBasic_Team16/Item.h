#pragma once
#include "stdafx.h"
#include "Entity.h"

class Item
{
private:
protected:
public:
	int count;
	float cooltime;
	float damage;
	float duration;
	bool active;
	sf::CircleShape shape;
	Item(float cooltime, float damage, float duration, sf::Vector2f position);
	virtual ~Item();
	virtual void initShape();
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy);
	virtual void render(sf::RenderTarget* target);
};