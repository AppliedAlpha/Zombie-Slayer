#pragma once

#include "stdafx.h"
#include "Inventory.h"

class Entity {
private:


protected:
	virtual void initShape();
	void initVariables(float movementSpeed, float power, float hp);

public:
	float power;
	float hp;
	Inventory inventory;
	float cx;
	float cy;
	float movementSpeed;
	float girdSize;
	sf::RectangleShape shape;

	Entity(float movementSpeed, float power, float hp);
	virtual ~Entity();

	virtual void move(const float& dt, const float dx, const float dy);
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	const sf::RectangleShape& getShape();
};