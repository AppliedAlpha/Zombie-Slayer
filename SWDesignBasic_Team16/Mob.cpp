#include "Mob.h"

void Mob::initShape(sf::Color color)
{
	Entity::initShape();
	this->shape.setSize(sf::Vector2f(this->girdSize, this->girdSize));
	this->shape.setFillColor(color);
	this->cx = Random::instance().getFloat(0, 100) + Random::instance().getInt(0, 1) * 1180.f;
	this->cy = Random::instance().getFloat(0, 720);
}

void Mob::updateCollision(Sword* sword)
{
	this->hp -= sword->damage;

	if (this->hp <= 0.f) {
		printf("Dead\n");
		this->onDeath();
	}
	else {
		std::cout << "Now " << this->name << ' ';
		printf("%.1f\n", this->hp);
	}
}

Mob::Mob() : Entity(1.5, 1.5, 100)
{
	this->name = "Zombie";
	this->initShape(sf::Color::Green);
	// this->initVariables();
}

Mob::Mob(const std::string& name, float movementSpeed, float power, float hp) : Entity(movementSpeed, power, hp)
{
	this->name = name;
	this->initShape(sf::Color::Blue);
}

Mob::Mob(const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size) : Entity(movementSpeed, power, hp) {
	this->name = name;
	this->girdSize = size;
	this->initShape(color);
}


Mob::~Mob()
{
}

void Mob::move(const float& dt, sf::Vector2f playerPosition) {
	auto dir = CustomMath::normalize(playerPosition - sf::Vector2f(this->cx, this->cy));

	float multiplyer = 20.f;
	this->cx += dir.x * this->movementSpeed * dt * multiplyer;
	this->cy += dir.y * this->movementSpeed * dt * multiplyer;
}

void Mob::update(const float& dt, sf::Vector2f playerPosition) {
	this->move(dt, playerPosition);
}

void Mob::render(sf::RenderTarget* target) {
	Entity::render(target);
}

void Mob::onDeath() {
	this->death = true;
	/*
	sf::Vector2f deathPosition = this->shape.getPosition();
	Inventory dropInventory;

	this->dropItems.push_back(DropItem(deathPosition, dropInventory));
	*/
}