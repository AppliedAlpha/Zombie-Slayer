#include "Mob.h"

void Mob::initShape(sf::Color color)
{
	Entity::initShape();
	this->shape.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	// if (color == sf::Color::Blue) this->shape.setSize(sf::Vector2f(this->gridSize + 20.f, this->gridSize + 20.f));
	this->shape.setFillColor(color);
	this->cx = 0;
	this->cy = 0;
}

void Mob::updateCollision(Weapon* weapon, float power)
{
	//std::cout << this->hp << std::endl;
	this->hp -= weapon->damage * power;

	if (this->hp <= 0.f) {
		this->onDeath();
	}
}

void Mob::updateItemCollision(Item* item, float power)
{
	this->hp -= item->damage * power;

	if (this->hp <= 0.f) {
		this->onDeath();
	}
}

void Mob::updateCollision(AoE* aoe)
{
	this->hp -= aoe->damage;

	if (this->hp <= 0.f) {
		this->onDeath();
	}
}

Mob::Mob() : Entity(1.5, 1.5, 100)
{
	this->name = "Zombie";
	this->initShape(sf::Color::Green);
	// this->initVariables();
}

Mob::Mob(int gold, int xp) : Entity(1.5, 1.5, 100)
{
	this->gold = gold;
	this->xp = xp;
	this->name = "Zombie";
	this->initShape(sf::Color::Green);
	this->direction = sf::Vector2f(0, 0);
	// this->initVariables();
}

Mob::Mob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size) : Entity(movementSpeed, power, hp) {
	this->gold = gold;
	this->xp = xp;
	this->name = name;
	this->gridSize = size;
	this->initShape(color);
	this->direction = sf::Vector2f(0, 0);
}

Mob::Mob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, Weapon* weapon) : Entity(movementSpeed, power, hp) {
	this->gold = gold;
	this->xp = xp;
	this->name = name;
	this->gridSize = size;
	this->initShape(color);
	this->weapon = weapon;
	this->direction = sf::Vector2f(0, 0);
}

Mob::~Mob()
{
	delete this->weapon;
}

void Mob::move(const float& dt, sf::Vector2f playerPosition) {
	//this->direction = CustomMath::normalize(playerPosition - sf::Vector2f(this->cx, this->cy));
	float multiplyer = 20.f;
	this->cx += this->direction.x * this->movementSpeed * dt * multiplyer;
	this->cy += this->direction.y * this->movementSpeed * dt * multiplyer;
}

void Mob::update(const float& dt, sf::Vector2f playerPosition) {
	this->move(dt, playerPosition);
	if (this->weapon)
		this->weapon->update(dt, this->shape, this->cx, this->cy, this->direction);
	Entity::update(dt);
}

void Mob::render(sf::RenderTarget* target) {
	if (this->weapon)
		this->weapon->render(target);
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