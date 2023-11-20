#pragma once

#include "Entity.h"
#include "Player.h"
#include "Sword.h"
#include "stdafx.h"
#include "DropItem.h"

class NPC : public Entity
{
private:

	void initShape(sf::Color color);
	bool death = false;

public:
	NPC();
	NPC(const std::string& name, float movementSpeed, float power, float hp);
	~NPC();

	std::string name;
	Inventory inventory;
	sf::Vector2f direction;
	float waitingTime;
	float movingTime;
	float time;
	bool moving;
	void updateCollision(Player player);

	void move(const float& dt);

	void updateDirection(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	void onDeath();
	bool getDeath() const { return this->death; }
};

