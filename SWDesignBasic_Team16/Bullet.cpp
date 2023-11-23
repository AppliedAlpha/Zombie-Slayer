#include "Bullet.h"

Bullet::Bullet(sf::RectangleShape& shape, sf::Vector2f direction, float speed, float duration)
{
	this->shape = shape;
	this->direction = direction;
	this->speed = speed;
	this->duration = duration;
	this->count = 0;
	this->out = false;
}

Bullet::~Bullet()
{
}

void Bullet::update(const float& dt, float cx, float cy)
{
	this->move();
	this->count++;
	if (this->count >= this->duration * 60) this->out = true;
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Bullet::move()
{
	this->shape.move(this->direction.x * this->speed, this->direction.y * this->speed);
}
