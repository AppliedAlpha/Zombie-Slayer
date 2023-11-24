#include "Brick.h"

Brick::Brick(float cooltime, float damage, float duration, sf::Vector2f position, float speed) : RangedWeapon(cooltime, damage, duration, position, speed)
{
	this->maxHitCount = 1000;
	initShape();
}

Brick::~Brick()
{
}

void Brick::initShape()
{
	RangedWeapon::initShape();
	this->shape.setSize(sf::Vector2f(60.f, 40.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);
}

void Brick::updateCollision(Entity* object)
{
}

void Brick::update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection)
{
	RangedWeapon::update(dt, playerPos, cx, cy, viewDirection);
	this->shape.setPosition(cx - this->shape.getGlobalBounds().width * 0.5f, cy - this->shape.getGlobalBounds().height * 0.5f);
}

void Brick::render(sf::RenderTarget* target)
{
	RangedWeapon::render(target);
}
