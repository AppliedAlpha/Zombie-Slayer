#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color) : Weapon(cooltime, damage, duration, position, color)
{
	this->shape.setPosition(position);
	initShape();
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::initShape()
{
}

void MeleeWeapon::updateCollision(Entity* object)
{
}

void MeleeWeapon::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
	Weapon::update(dt, playerShape, cx, cy, viewDirection);
	if (this->active && this->count >= this->duration * 60) {
		this->active = false;
		this->count = 0;
	}
	if (!this->active && this->count >= this->duration * 60 && this->count >= this->cooltime * 60) {
		this->active = true;
		this->count = 0;
	}

	this->count++;
}

void MeleeWeapon::render(sf::RenderTarget* target)
{
}

void MeleeWeapon::levelUp()
{
}
