#pragma once
#include "Item.h"

class AoeItem : public Item
{
private:

protected:
public:
	AoeItem(float cooltime, float damage, float duration, sf::Vector2f position);
	virtual ~AoeItem();
	sf::CircleShape shape;

	virtual void initShape();
	virtual void updateCollision(Entity* object);
	virtual void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy);
	virtual void render(sf::RenderTarget* target);
};