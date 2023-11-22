#pragma once
#include "Item.h"

class AoeItem : public Item
{
public:
	AoeItem(float cooltime, float damage, float duration);
	~AoeItem();
	sf::CircleShape shape;

	virtual void initShape();

};