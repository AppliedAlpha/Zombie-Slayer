#include "Entity.h"

void Entity::initShape()
{
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(2.f);
}

void Entity::initVariables(float movementSpeed, float power, float hp)
{
	this->movementSpeed = movementSpeed;
	this->maxHp = hp;
	this->power = power;
	this->hp = hp;
	this->cx = 0.f;
	this->cy = 0.f;
	this->gridSize = 20.f;
	this->level = 1;
}

Entity::Entity(float movementSpeed, float power, float hp) {
	initVariables(movementSpeed, power, hp);
	Entity::initShape();
}

Entity::~Entity() {
}

void Entity::initHpBar()
{
	float bottomPadding = 5.f;
	float height = 5.f;
	
	hpBar[0] = sf::Vertex(sf::Vector2f(this->cx - (this->gridSize + 8.f) * 0.5, this->cy + this->gridSize * 0.5 + bottomPadding), sf::Color::Red);
	hpBar[1] = sf::Vertex(sf::Vector2f(this->cx - (this->gridSize + 8.f) * 0.5, this->cy + this->gridSize * 0.5 + height + bottomPadding), sf::Color::Red);
	hpBar[2] = sf::Vertex(sf::Vector2f(this->cx + (this->gridSize) * 0.5, this->cy + this->gridSize * 0.5 + height + bottomPadding), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(this->cx + (this->gridSize) * 0.5, this->cy + this->gridSize * 0.5 + bottomPadding), sf::Color::Red);
}

void Entity::updateHpBar()
{
	float bottomPadding = 5.f;
	float height = 5.f;
	float scale = (this->gridSize + 4.f) / this->maxHp;
	hpBar[0] = sf::Vertex(sf::Vector2f(this->cx - (this->gridSize + 8.f) * 0.5, this->cy + this->gridSize * 0.6 + bottomPadding), sf::Color::Red);
	hpBar[1] = sf::Vertex(sf::Vector2f(this->cx - (this->gridSize + 8.f) * 0.5, this->cy + this->gridSize * 0.6 + height + bottomPadding), sf::Color::Red);
	hpBar[2] = sf::Vertex(sf::Vector2f(this->cx - (this->gridSize + 8.f) * 0.5 + this->hp * scale, this->cy + this->gridSize * 0.6 + height + bottomPadding), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(this->cx - (this->gridSize + 8.f) * 0.5 + this->hp * scale, this->cy + this->gridSize * 0.6 + bottomPadding), sf::Color::Red);
}

void Entity::move(const float& dt, const float dx, const float dy) {
}

void Entity::updateCollision(Entity* object)
{
}

void Entity::update(const float& dt)
{
	if (this->cx < -640) this->cx = -640;
	if (this->cx > 1920) this->cx = 1920;
	if (this->cy < -360) this->cy = -360;
	if (this->cy > 1080) this->cy = 1080;
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

void Entity::renderHpBar(sf::RenderTarget* target) {
	target->draw(this->hpBar, 4, sf::Quads);
}

const sf::RectangleShape& Entity::getShape()
{
	return this->shape;
}

