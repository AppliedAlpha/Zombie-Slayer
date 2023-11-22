#include "Item.h"

Item::Item(float cooltime, float damage, float duration)
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

void Item::update(const float& dt, sf::FloatRect pos)
{
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}