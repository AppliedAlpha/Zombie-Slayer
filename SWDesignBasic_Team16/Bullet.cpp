#include "Bullet.h"

Bullet::Bullet(sf::RectangleShape& shape, sf::Vector2f direction, float speed, float duration, int maxHitCount, bool explosion)
{
	this->shape = shape;
	this->direction = direction;
	this->speed = speed;
	this->duration = duration;
	this->count = 0;
	this->out = false;
	this->hitCount = 1;
	this->maxHitCount = maxHitCount;
	this->explosion = explosion;
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
	this->direction = CustomMath::normalize(this->direction);
	this->shape.move(this->direction.x * this->speed, this->direction.y * this->speed);
}

AoE* Bullet::explode(float radius, float duration, float damage, sf::Vector2f position)
{
	return new AoE(radius, duration, damage, position);
}
