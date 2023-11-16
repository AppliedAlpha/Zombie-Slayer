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
	void update(const float& dt, sf::FloatRect pos);
	void render(sf::RenderTarget* target);
};