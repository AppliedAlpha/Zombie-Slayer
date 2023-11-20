#include "Entity.h"

void Entity::initShape()
{
}

void Entity::initVariables(float movementSpeed, float power, float hp)
{
	this->movementSpeed = movementSpeed;
	this->power = power;
	this->hp = hp;
	this->cx = 0.f;
	this->cy = 0.f;
	this->gridSize = 20.f;
}

Entity::Entity(float movementSpeed, float power, float hp) {
	initVariables(movementSpeed, power, hp);
	initHpBar();
}

Entity::~Entity() {
}

void Entity::initHpBar()
{
	hpBar[0] = sf::Vertex(sf::Vector2f(this->cx - 50.f, this->cy + this->gridSize * 0.5), sf::Color::Red);
	hpBar[1] = sf::Vertex(sf::Vector2f(this->cx - 50.f, this->cy + this->gridSize), sf::Color::Red);
	hpBar[2] = sf::Vertex(sf::Vector2f(this->cx + 50.f, this->cy + this->gridSize), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(this->cx + 50.f, this->cy + this->gridSize * 0.5), sf::Color::Red);
}

void Entity::updateHpBar()
{
	hpBar[0] = sf::Vertex(sf::Vector2f(this->cx - 50.f, this->cy + this->gridSize * 0.5), sf::Color::Red);
	hpBar[1] = sf::Vertex(sf::Vector2f(this->cx - 50.f, this->cy + this->gridSize), sf::Color::Red);
	hpBar[2] = sf::Vertex(sf::Vector2f(this->cx + (this->hp - 50.f), this->cy + this->gridSize), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(this->cx + (this->hp - 50.f), this->cy + this->gridSize * 0.5), sf::Color::Red);
}

void Entity::move(const float& dt, const float dx, const float dy) {
}

void Entity::updateCollision(Entity* object)
{
}

void Entity::update(const float& dt)
{
	updateHpBar();
}

void Entity::render(sf::RenderTarget* target) {
	sf::FloatRect pos = this->shape.getGlobalBounds();
	pos.left = this->cx - (pos.width * 0.5f);
	pos.top = this->cy - (pos.height * 0.5f);
	this->shape.setPosition(pos.left, pos.top);
	this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
	target->draw(this->shape);
	target->draw(this->hpBar, 4, sf::Quads);
}

const sf::RectangleShape& Entity::getShape()
{
	return this->shape;
}