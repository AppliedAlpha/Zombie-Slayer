#include "Spear.h"

Spear::Spear(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color) : MeleeWeapon(cooltime, damage, duration, position, color)
{
	initShape();
}

Spear::~Spear()
{
}

void Spear::initShape()
{
	MeleeWeapon::initShape();
	this->shape.setSize(sf::Vector2f(24.f, 100.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
}

void Spear::updateCollision(Entity* object)
{
}

void Spear::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
	MeleeWeapon::update(dt, playerShape, cx, cy, viewDirection);
	sf::FloatRect pos;
	pos.left = cx - (this->shape.getGlobalBounds().width * 0.5f);
	pos.top = cy - (this->shape.getGlobalBounds().height * 0.5f);
	float angle = this->getViewAngle(viewDirection);
	if (angle != 0.f) {
		this->shape.setPosition(cx - playerShape.getGlobalBounds().width * 0.5f, cy - playerShape.getGlobalBounds().height * 0.5f);
		this->shape.setOrigin(playerShape.getOrigin());
		this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
		this->shape.setRotation(angle - 45);
	}
}

void Spear::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Spear::levelUp()
{
	switch (this->level)
	{
	case 1:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->level++;
		break;
	case 2:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->level++;
		break;
	case 3:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(10.f, 10.f));
		this->level++;
		break;
	default:
		break;
	}
}
