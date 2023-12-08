#include "Brick.h"

Brick::Brick(float cooltime, float damage, float duration, sf::Vector2f position, float speed, sf::Color color) : RangedWeapon(cooltime, damage, duration, position, speed, color)
{
	this->maxHitCount = INT16_MAX;
	initShape();
}

Brick::~Brick()
{
}

void Brick::initShape()
{
	RangedWeapon::initShape();
	this->shape.setSize(sf::Vector2f(60.f, 40.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
}

void Brick::updateCollision(Entity* object)
{
}

void Brick::update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection)
{
	RangedWeapon::update(dt, playerPos, cx, cy, viewDirection);
	this->shape.setPosition(cx - this->shape.getGlobalBounds().width * 0.5f - this->shape.getOutlineThickness(), cy - this->shape.getGlobalBounds().height * 0.5f - this->shape.getOutlineThickness());
}

void Brick::render(sf::RenderTarget* target)
{
	RangedWeapon::render(target);
}

void Brick::levelUp()
{
	switch (this->level)
	{
	case 1:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->damage += .1f;
		this->level++;
		break;
	case 2:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->damage += .1f;
		this->level++;
		break;
	case 3:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(20.f, 20.f));
		this->damage += .3f;
		this->duration += 3.f;
		this->cooltime -= 2.f;
		this->level++;
		break;
	default:
		break;
	}
}
