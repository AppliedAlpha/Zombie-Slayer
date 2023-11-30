#include "Bomb.h"

Bomb::Bomb(float cooltime, float damage, float duration, sf::Vector2f position) : AoeItem(cooltime, damage, duration, position)
{
	initShape();
}

Bomb::~Bomb()
{
}

void Bomb::initShape()
{
	AoeItem::initShape();
	this->shape.setRadius(400.f);
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);
}

void Bomb::updateCollision(Entity* object)
{
}

void Bomb::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy)
{
	AoeItem::update(dt, playerShape, cx, cy);
	
	this->shape.setPosition(cx - shape.getRadius(), cy - shape.getRadius());

}

void Bomb::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
