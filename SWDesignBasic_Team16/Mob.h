#pragma once

#include "Entity.h"
#include "Sword.h"
#include "stdafx.h"
#include "DropItem.h"

class Mob : public Entity
{
private:

	void initShape(sf::Color color);
	bool death = false;

public:
	Mob();
	Mob(const std::string& name, float movementSpeed, float power, float hp);
	~Mob();

	std::string name;
	Inventory inventory;
	void updateCollision(Weapon* weapon, float power);

	void move(const float& dt, sf::Vector2f playerPosition);

	void update(const float& dt, sf::Vector2f playerPosition);
	void render(sf::RenderTarget* target);

	void onDeath();
	bool getDeath() const { return this->death; }
};