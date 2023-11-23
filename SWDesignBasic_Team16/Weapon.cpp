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

void Weapon::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
}

void Weapon::render(sf::RenderTarget* target)
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