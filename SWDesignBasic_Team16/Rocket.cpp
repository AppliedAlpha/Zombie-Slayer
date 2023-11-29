#include "Rocket.h"

Rocket::Rocket(float cooltime, float damage, float duration, sf::Vector2f position, float speed, sf::Color color, float radius, float explosionDamage, float explosionDuration) : RangedWeapon(cooltime, damage, duration, position, speed, color, radius, explosionDamage, explosionDuration)
{
	this->initShape();
}

Rocket::~Rocket()
{
}

void Rocket::initShape()
{
	RangedWeapon::initShape();
	this->shape.setSize(sf::Vector2f(30.f, 30.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
}

void Rocket::updateCollision(Entity* object)
{
}

void Rocket::update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection)
{
	RangedWeapon::update(dt, playerPos, cx, cy, viewDirection);
	this->shape.setPosition(cx - this->shape.getGlobalBounds().width * 0.5f - this->shape.getOutlineThickness(), cy - this->shape.getGlobalBounds().height * 0.5f - this->shape.getOutlineThickness());
}

void Rocket::render(sf::RenderTarget* target)
{
	RangedWeapon::render(target);
}

void Rocket::levelUp()
{
	switch (this->level)
	{
	case 1:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->level++;
		break;
	case 2:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->level++;
		break;
	case 3:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->level++;
		break;
	default:
		break;
	}
}
