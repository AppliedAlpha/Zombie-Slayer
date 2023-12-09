#pragma once

#include "Entity.h"
#include "Sword.h"
#include "Bomb.h"
#include "AoE.h"
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
	Mob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, sf::Sprite* sprite = nullptr, Weapon* weapon = nullptr);
	~Mob();

	bool freeze = false;
	bool isSprite = false;
	float speedZeroDuration;
	float originSpeed;
	Weapon* weapon = nullptr;
	std::string name;
	Inventory inventory;
	sf::Vector2f direction;
	sf::Sprite sprite;

	void updateCollision(AoE* aoe, float power);
	void updateCollision(Weapon* weapon, float power);
	void updateItemCollision(Item* item, float power);

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