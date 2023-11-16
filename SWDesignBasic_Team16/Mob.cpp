#include "Mob.h"

void Mob::initShape()
{
	Entity::initShape();
	this->shape.setSize(sf::Vector2f(this->girdSize, this->girdSize));
	this->shape.setFillColor(sf::Color::Green);
	// this->cx = (rand() % 8) * 100;
	// this->cy = (rand() % 8) * 100;
	this->cx = Random::instance().getFloat(0, 100) + Random::instance().getInt(0, 1) * 1180.f;
	this->cy = Random::instance().getFloat(0, 720);
}

void Mob::updateCollision(Sword* sword)
{
	this->hp -= sword->damage;
	if (this->hp <= 0.f) printf("Dead\n");
	else printf("%.1f\n", this->hp);
}

Mob::Mob() : Entity(0, 1, 100)
{
	initShape();
}

Mob::~Mob()
{
}