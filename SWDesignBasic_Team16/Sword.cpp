#include "Sword.h"

void Sword::initShape()
{
	MeleeWeapon::initShape();
	this->shape.setSize(sf::Vector2f(60.f, 60.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
}

void Sword::updateCollision(Entity* object)
{
}

void Sword::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
	MeleeWeapon::update(dt, playerShape, cx, cy, viewDirection);
	float angle = this->getViewAngle(viewDirection);
	if (angle != 0.f) {
		this->shape.setPosition(cx - playerShape.getGlobalBounds().width * 0.5f, cy - playerShape.getGlobalBounds().height * 0.5f - this->shape.getOutlineThickness());
		this->shape.setOrigin(playerShape.getOrigin());
		this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
		this->shape.setRotation(angle);
	}
}

void Sword::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Sword::levelUp()
{
	switch (this->level)
	{
	case 1:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(5, 5));
		this->cooltime = this->cooltime - 0.1f;
		this->level++;
		break;
	case 2:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(5, 5));
		this->cooltime = this->cooltime - 0.1f;
		this->level++;
		break;
	case 3:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->damage = this->damage + 1.f;
		this->cooltime = this->cooltime - 0.3f;
		this->level++;
		break;
	default:
		break;
	}
}

Sword::Sword(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color) : MeleeWeapon(cooltime, damage, duration, position, color)
{
	initShape();
}

Sword::~Sword()
{
};