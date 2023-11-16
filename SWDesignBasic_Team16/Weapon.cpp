#include "Weapon.h"

Weapon::Weapon(float cooltime, float damage, float duration)
{
	this->count = 0;
	this->cooltime = cooltime;
	this->damage = damage;
	this->duration = duration;
	this->active = false;
}

Weapon::~Weapon()
{
}

void Weapon::update(const float& dt, sf::FloatRect pos)
{
}

void Weapon::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}