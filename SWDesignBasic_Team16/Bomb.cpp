#include "Bomb.h"

void Bomb::initShape()
{
	AoeItem::initShape();
	this->shape.setRadius(400.f);
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);
	this->shape.setPosition(1280.f / 2, 720.f / 2);

	/*this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);*/
	// this->shape.setOrigin(50, 50);
}

void Bomb::updateCollision(Entity* object)
{
}

void Bomb::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy)
{
	this->shape.setPosition(cx - shape.getRadius(), cy - shape.getRadius());
}

void Bomb::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

Bomb::Bomb(float cooltime, float damage, float duration) : AoeItem(cooltime, damage, duration)
{
	initShape();
}

Bomb::~Bomb()
{
}