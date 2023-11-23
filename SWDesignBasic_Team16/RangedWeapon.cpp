#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(float cooltime, float damage, float duration, sf::Vector2f position, float speed) : Weapon(cooltime, damage, duration, position)
{
	this->speed = speed;
	this->shape.setPosition(position);
	this->activeDirection = sf::Vector2f(0.f, 1.f);
	
}

RangedWeapon::~RangedWeapon()
{
}

void RangedWeapon::initShape()
{
}

void RangedWeapon::updateCollision(Entity* object)
{
}

void RangedWeapon::update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection)
{
	Weapon::update(dt, playerPos, cx, cy, viewDirection);

	this->count++;
	if (this->count >= this->cooltime * 60) {
		this->active = false;
		this->bullets.push_back(new Bullet(this->shape, this->activeDirection, this->speed, this->duration));
		this->count = 0;
	}
	else {
		if (viewDirection.x != 0 || viewDirection.y != 0) this->activeDirection = viewDirection;
	}

	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i)->update(dt, cx, cy);
		if (this->bullets.front()->out) {
			delete this->bullets.front();
			this->bullets.pop_front();
		}
	}
}

void RangedWeapon::render(sf::RenderTarget* target)
{
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i)->render(target);
	}
}
