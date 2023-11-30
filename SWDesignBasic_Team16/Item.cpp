#include "Item.h"

Item::Item(float cooltime, float damage, float duration, sf::Vector2f position)
{
	this->count = 0;
	this->cooltime = cooltime;
	this->damage = damage;
	this->duration = duration;
	this->active = false;
}

Item::~Item()
{
}

void Item::initShape()
{
}

void Item::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy)
{
}

void Item::render(sf::RenderTarget* target)
{
}