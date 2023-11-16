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
	this->girdSize = 20.f;
}

Entity::Entity(float movementSpeed, float power, float hp) {
	initVariables(movementSpeed, power, hp);
}

Entity::~Entity() {
}

void Entity::move(const float& dt, const float dx, const float dy) {
}

void Entity::updateCollision(Entity* object)
{
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target) {
	sf::FloatRect pos = this->shape.getGlobalBounds();
	pos.left = this->cx - (pos.width * 0.5f);
	pos.top = this->cy - (pos.height * 0.5f);
	this->shape.setPosition(pos.left, pos.top);
	this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
	target->draw(this->shape);
}

const sf::RectangleShape& Entity::getShape()
{
	return this->shape;
}