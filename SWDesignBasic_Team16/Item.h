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
	Item(float cooltime, float damage, float duration);
	~Item();
	void update(const float& dt, sf::FloatRect pos);
	void render(sf::RenderTarget* target);
};