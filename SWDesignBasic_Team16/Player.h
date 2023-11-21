#pragma once

#include "Mob.h"
#include "NPC.h"
#include "Sword.h"
#include "Sword.h"
#include "Spear.h"
#include "Grinder.h"

class Player : public Entity
{
private:
	void initShape();
	void initVariables();
	bool death = false;

public:
	bool invincible = true;
	sf::Vector2f viewDirection;
	std::vector<Weapon*> weaponList;
	Inventory inventory;
	Player();
	~Player();
	void attack(const float& dt);
	void updateLevel(const float& dt);
	void updateCollision(Entity* obejct);
	void move(const float& dt, const float dx, const float dy);
	void render(sf::RenderTarget* target);
	void update(const float& dt, sf::Vector2f velocity);
	float getViewAngle();
	
	bool getDeath() const { return this->death; }
};