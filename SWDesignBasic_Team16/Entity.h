#pragma once

#include "stdafx.h"
#include "Inventory.h"

class Entity {
private:

protected:
	virtual void initShape();
	void initVariables(float movementSpeed, float power, float hp);

public:
	int level;
	float power;
	float hp;
	float maxHp;
	Inventory inventory;
	float cx;
	float cy;
	float movementSpeed;
	float gridSize;
	sf::RectangleShape shape;
	sf::Vertex hpBar[4];
	float hpBarLength = 40;

	Entity(float movementSpeed, float power, float hp);
	virtual ~Entity();

	void initHpBar();
	void updateHpBar();
	virtual void move(const float& dt, const float dx, const float dy);
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	void renderHpBar(sf::RenderTarget* target);
	const sf::RectangleShape& getShape();
};