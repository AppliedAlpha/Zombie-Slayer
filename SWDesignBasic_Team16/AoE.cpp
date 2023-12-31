#include "AoE.h"

AoE::AoE(float radius, float duration, float damage, sf::Vector2f position)
{
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color(255, 0, 0, 100));
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);
	this->shape.setPosition(position);
	this->shape.setOrigin(radius, radius);
	this->duration = duration;
	this->damage = damage;
	this->count = 0;
	this->slowRate = 0;
	this->disappear = false;
	this->mobTarget = true;
}

AoE::AoE(float radius, float duration, sf::Vector2f position, float slowRate)
{
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color(0, 183, 235, 100));
	this->shape.setOutlineColor(sf::Color::Cyan);
	this->shape.setOutlineThickness(2.f);
	this->shape.setPosition(position);
	this->shape.setOrigin(radius, radius);
	this->damage = 0;
	this->duration = duration;
	this->slowRate = slowRate;
	this->count = 0;
	this->disappear = false;
	this->mobTarget = true;
}

AoE::AoE(float radius, float duration, float damage, sf::Vector2f position, bool mobTarget) {
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color(0, 255, 0, 100));
	this->shape.setOutlineColor(sf::Color(0, 255, 0));
	this->shape.setOutlineThickness(2.f);
	this->shape.setPosition(position);
	this->shape.setOrigin(radius, radius);
	this->duration = duration;
	this->damage = damage;
	this->count = 0;
	this->disappear = false;
	this->mobTarget = false;
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