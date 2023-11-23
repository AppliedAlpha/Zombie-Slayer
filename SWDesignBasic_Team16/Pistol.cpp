#include "Pistol.h"

Pistol::Pistol(float cooltime, float damage, float duration, sf::Vector2f position, float speed) : RangedWeapon(cooltime, damage, duration, position, speed)
{
	this->initShape();
}

Pistol::~Pistol()
{
}

void Pistol::initShape()
{
	RangedWeapon::initShape();
	this->shape.setSize(sf::Vector2f(20.f, 20.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);

	/*this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);*/
	// this->shape.setOrigin(50, 50);
}

void Pistol::updateCollision(Entity* object)
{
}

void Pistol::update(const float& dt, sf::RectangleShape playerPos, float cx, float cy, sf::Vector2f viewDirection)
{
	RangedWeapon::update(dt, playerPos, cx, cy, viewDirection);
	this->shape.setPosition(cx - playerPos.getGlobalBounds().width * 0.5f, cy - playerPos.getGlobalBounds().height * 0.5f);
}

void Pistol::render(sf::RenderTarget* target)
{
	RangedWeapon::render(target);
	// target->draw(this->shape);
}
