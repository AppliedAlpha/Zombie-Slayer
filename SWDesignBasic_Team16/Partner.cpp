#include "Partner.h"

void Partner::initShape()
{
	this->shape.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->shape.setFillColor(sf::Color::Yellow);

	this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
	this->shape.setRotation(45);
	this->initHpBar();
}

Partner::Partner(float cx, float cy, sf::Vector2f viewDirection, int index) : Entity(100, 1, 300)
{
	this->index = index;
	sf::Vector2f center;
	if (viewDirection.x == 0.f && viewDirection.y == 0) {
		center = sf::Vector2f(cx, cy) - sf::Vector2f(1.0f, 0.f) * (30.f * this->index);
		this->viewDirection = sf::Vector2f(1.0f, 0.f);
	}
	else if (viewDirection.x * viewDirection.x + viewDirection.y * viewDirection.y == 2) {
		center = sf::Vector2f(cx, cy) - viewDirection * (15.f * this->index);
		this->viewDirection = viewDirection;
	}
	else {
		center = sf::Vector2f(cx, cy) - viewDirection * (30.f * this->index);
		this->viewDirection = viewDirection;
	}
	this->cx = center.x;
	this->cy = center.y;
	this->initShape();
	// new Pistol(.5f, 5, 5.f, sf::Vector2f(this->player->cx, this->player->cy), 5, sf::Color::Red)
	this->weapon = new Pistol(1.f, 5, 5.f, sf::Vector2f(this->cx, this->cy), 5, sf::Color::Red);
}

Partner::~Partner()
{
	delete this->weapon;
}

void Partner::attack(const float& dt)
{
	this->weapon->update(dt, this->shape, this->cx, this->cy, this->viewDirection);
}

void Partner::updateCollision(Entity* object)
{
	if (Mob* mob = dynamic_cast<Mob*>(object)) {
		this->hp -= mob->power;
	}
}

void Partner::updateCollision(Weapon* weapon)
{
	this->hp -= weapon->damage;
}

void Partner::updateCollision(AoE* aoe)
{
	this->hp -= aoe->damage;
}

void Partner::move(const float& dt, float cx, float cy, sf::Vector2f viewDirection)
{
	this->viewDirection = viewDirection;
	if (viewDirection.x != 0.f || viewDirection.y != 0) {
		sf::Vector2f center;
		if (viewDirection.x * viewDirection.x + viewDirection.y * viewDirection.y == 2) {
			center = sf::Vector2f(cx, cy) - viewDirection * (15.f * this->index);
		}
		else {
			center = sf::Vector2f(cx, cy) - viewDirection * (30.f * this->index);
		}
		this->cx = center.x;
		this->cy = center.y;
	}
}

void Partner::render(sf::RenderTarget* target)
{
	this->renderHpBar(target);
	Entity::render(target);
}

void Partner::update(const float& dt, float cx, float cy, sf::Vector2f viewDirection)
{
	this->updateHpBar();
	this->move(dt, cx, cy, viewDirection);
	this->attack(dt);
	if (this->hp <= 0) this->death = true;
	Entity::update(dt);
}
