#pragma once
#include "Entity.h"
#include "Pistol.h"
#include "AoE.h"
#include "Mob.h"

class Partner : public Entity
{
private:
	void initShape();
	bool death = false;

public:
	int index;
	bool invincible = true;
	sf::Vector2f viewDirection;
	Weapon* weapon;
	Partner(float cx, float cy, sf::Vector2f viewDirection, int index);
	~Partner();
	void attack(const float& dt);
	void updateCollision(Entity* obejct);
	void updateCollision(Weapon* weapon);
	void updateCollision(AoE* aoe);
	void move(const float& dt, float cx, float cy, sf::Vector2f viewDirection);
	void render(sf::RenderTarget* target);
	void update(const float& dt, float cx, float cy, sf::Vector2f viewDirection);

	bool getDeath() const { return this->death; }
};

