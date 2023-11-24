#include "AoE.h"

AoE::AoE(float radius, float duration, float damage, sf::Vector2f position)
{
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);
	this->shape.setPosition(position);
	this->shape.setOrigin(radius, radius);
	this->duration = duration;
	this->damage = damage;
	this->count = 0;
	this->disappear = false;
}

AoE::~AoE()
{
}

void AoE::update(const float& dt)
{
	if (this->count >= this->duration * 60) this->disappear = true;
	this->count++;
}

void AoE::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
