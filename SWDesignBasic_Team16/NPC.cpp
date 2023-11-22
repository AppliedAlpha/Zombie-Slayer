#include "NPC.h"

void NPC::initShape(sf::Color color)
{
	Entity::initShape();
	this->shape.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->shape.setFillColor(color);
	this->cx = Random::instance().getFloat(500, 600);
	this->cy = Random::instance().getFloat(300, 500);
	this->shape.setPosition(this->cx, this->cy);
}

NPC::NPC() : Entity(5, 1.5, 100)
{
	this->moving = false;
	this->direction = sf::Vector2f(0, 0);
	this->waitingTime = 1.f;
	this->movingTime = .5f;
	this->time = 0.f;
	initShape(sf::Color::Yellow);
}

NPC::NPC(const std::string& name, float movementSpeed, float power, float hp) : Entity(movementSpeed, power, hp)
{
	this->moving = false;
	this->direction = sf::Vector2f(0, 0);
	this->waitingTime = 3.f;
	this->movingTime = 1.f;
	this->time = 0.f;
	initShape(sf::Color::Yellow);
}

NPC::~NPC()
{
}

void NPC::move(const float& dt)
{
	float multiplyer = 20.f;
	this->cx += this->direction.x * this->movementSpeed * dt * multiplyer;
	this->cy += this->direction.y * this->movementSpeed * dt * multiplyer;
}

void NPC::updateDirection(const float& dt)
{
	int x = rand() % 2;
	int y = rand() % 2;
	this->direction = sf::Vector2f(x, y);
}

void NPC::update(const float& dt)
{
	Entity::update(dt);
	this->time += 1.f;
	if (!this->moving && this->time >= this->waitingTime * 60) {
		updateDirection(dt);
		this->moving = true;
		this->time = 0;
	}
	if (this->moving && this->time >= this->movingTime * 60) {
		this->moving = false;
		this->time = 0;
	}
	if (this->moving) {
		move(dt);
	}
}

void NPC::render(sf::RenderTarget* target)
{
	Entity::render(target);
}

void NPC::onDeath()
{
}
