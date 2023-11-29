#pragma once

#include "Mob.h"
#include "NPC.h"
#include "Sword.h"
#include "Sword.h"
#include "Spear.h"
#include "Grinder.h"
#include "stdafx.h"
#include "Bomb.h"
#include "Pistol.h"
#include "Brick.h"
#include "Rocket.h"

class Player : public Entity
{
private:
	void initShape();
	void initVariables();
	bool death = false;

public:
	bool invincible = true;
	sf::Vector2f viewDirection;
	std::unordered_map<int, Weapon*> weaponList;
	std::vector<int> selected;
	std::vector<int> unselected;
	Inventory inventory;
	Bomb* bomb;
	Player();
	~Player();
	void attack(const float& dt);
	void updateLevel(const float& dt);
	void updateCollision(Entity* obejct);
	void updateCollision(Weapon* weapon);
	void updateCollision(AoE* aoe);
	void move(const float& dt, const float dx, const float dy);
	void render(sf::RenderTarget* target);
	void update(const float& dt, sf::Vector2f velocity);
	std::string indexToWeaponName(int index);
	int weaponNameToIndex(std::string name);

	bool getDeath() const { return this->death; }
};