#pragma once
#include "Entity.h"
#include "Sword.h"

class Player : public Entity
{
private:
	void initShape();
	void initVariables();
	bool death = false;

public:
	sf::Vector2f viewDirection;
	Sword* sword;
	Player();
	~Player();
	void attack();
	void updateCollision(Entity* obejct, sf::Vector2f& velocity);
	void move(const float& dt, const float dx, const float dy);
	void render(sf::RenderTarget* target);
	void update(const float& dt, sf::Vector2f velocity);
	float getViewAngle();
	
	bool getDeath() const { return this->death; }
};