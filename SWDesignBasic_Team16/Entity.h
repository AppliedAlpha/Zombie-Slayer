#pragma once

#include "stdafx.h"

class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	virtual void move(const float& dt, const float dx, const float dy);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

