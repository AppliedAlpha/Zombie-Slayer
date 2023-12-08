#include "Pistol.h"

Pistol::Pistol(float cooltime, float damage, float duration, sf::Vector2f position, float speed, sf::Color color) : RangedWeapon(cooltime, damage, duration, position, speed, color)
{
	this->maxHitCount = 1;
	this->initShape();
}

Pistol::~Pistol()
{
}

void Pistol::initShape()
{
	RangedWeapon::initShape();
	this->shape.setSize(sf::Vector2f(10.f, 10.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
}

void Pistol::updateCollision(Entity* object)
{
}

void Pistol::update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection)
{
	RangedWeapon::update(dt, playerPos, cx, cy, viewDirection);
	this->shape.setPosition(cx - this->shape.getGlobalBounds().width * 0.5f - this->shape.getOutlineThickness(), cy - this->shape.getGlobalBounds().height * 0.5f - this->shape.getOutlineThickness());
	
}

void Pistol::render(sf::RenderTarget* target)
{
	RangedWeapon::render(target);
}

void Pistol::levelUp()
{
	switch (this->level)
	{
	case 1:
		this->damage += 2.5f;
		this->maxHitCount += 1;
		this->level++;
		break;
	case 2:
		this->damage += 2.5f;
		this->maxHitCount += 1;
		this->level++;
		break;
	case 3:
		this->damage += 5.f;
		this->maxHitCount += 2;
		this->duration += 1.f;
		this->speed += 2.f;
		this->level++;
		break;
	default:
		break;
	}
}
