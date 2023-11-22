#pragma once

#include "Entity.h"
#include "Sword.h"
#include "Bomb.h"
#include "stdafx.h"
#include "DropItem.h"

class Mob : public Entity
{
private:
	int gold;
	int xp;

	void initShape(sf::Color color);
	bool death = false;

public:
	Mob();
	Mob(int gold, int xp);
	//Mob(const std::string& name, float movementSpeed, float power, float hp);
	Mob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size);
	// Mob(const std::string& name, float power, float movementSpeed, float hp, const sf::Color& color, float size);
	~Mob();

	std::string name;
	Inventory inventory;
	void updateCollision(Bomb* bomb);
	void updateCollision(Weapon* weapon, float power);

	void move(const float& dt, sf::Vector2f playerPosition);

	void update(const float& dt, sf::Vector2f playerPosition);
	void render(sf::RenderTarget* target);

	void onDeath();
	bool getDeath() const { return this->death; }
	int getGold() const {
		return this->gold;
	}

	int getXP() const {
		return this->xp;
	}
};