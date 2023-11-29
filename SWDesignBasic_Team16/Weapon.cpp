#include "Weapon.h"

Weapon::Weapon(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color)
{
	this->level = 1;
	this->maxLevel = 4;
	this->count = 0;
	this->cooltime = cooltime;
	this->damage = damage;
	this->duration = duration;
	this->active = false;
	initShape(color);
}

Weapon::~Weapon()
{
}

void Weapon::initShape(sf::Color color)
{
	this->shape.setFillColor(sf::Color(color.r, color.g, color.b, 100));
	this->shape.setOutlineColor(color);
	this->shape.setOutlineThickness(2.f);
}

void Weapon::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
}

void Weapon::render(sf::RenderTarget* target)
{
}

void Weapon::levelUp()
{
}

float Weapon::getViewAngle(sf::Vector2f viewDirection)
{
	float angle = 0.f;
	if (viewDirection.x == 0.f && viewDirection.y == 1.f) {
		angle = 45.f;
	}
	else if (viewDirection.x == -1.f && viewDirection.y == 1.f) {
		angle = 90.f;
	}
	else if (viewDirection.x == -1.f && viewDirection.y == 0.f) {
		angle = 135.f;
	}
	else if (viewDirection.x == -1.f && viewDirection.y == -1.f) {
		angle = 180.f;
	}
	else if (viewDirection.x == 0.f && viewDirection.y == -1.f) {
		angle = 225.f;
	}
	else if (viewDirection.x == 1.f && viewDirection.y == -1.f) {
		angle = 270.f;
	}
	else if (viewDirection.x == 1.f && viewDirection.y == 0.f) {
		angle = 315.f;
 	}
	else if (viewDirection.x == 1.f && viewDirection.y == 1.f) {
		angle = 360.f;
	}
	return angle;
}