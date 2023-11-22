#include "Weapon.h"

Weapon::Weapon(float cooltime, float damage, float duration, sf::Vector2f position)
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

void Weapon::initShape()
{
}

void Weapon::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle)
{
	if (this->active && this->count >= this->duration * 60) {
		this->active = false;
		this->count = 0;
	}
	if (!this->active && this->count >= this->cooltime * 60) {
		this->active = true;
		this->count = 0;
	}

	this->count++;
}

void Weapon::render(sf::RenderTarget* target)
{
}