#include "Grinder.h"

Grinder::Grinder(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color) : MeleeWeapon(cooltime, damage, duration, position, color)
{
	this->rotation = 0;
	this->rotationSpeed = 10;
	initShape();
}

Grinder::~Grinder()
{
}

void Grinder::initShape()
{
	MeleeWeapon::initShape();
	this->shape.setSize(sf::Vector2f(50.f, 50.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
}

void Grinder::updateCollision(Entity* object)
{
}

void Grinder::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
	MeleeWeapon::update(dt, playerShape, cx, cy, viewDirection);
	rotation += 1 * this->rotationSpeed;
	if (rotation == 360) rotation = 0;
	sf::FloatRect pos;
	pos.left = cx - (this->shape.getGlobalBounds().width * 0.5f);
	pos.top = cy - (this->shape.getGlobalBounds().height * 0.5f);
	float angle = this->getViewAngle(viewDirection);
	this->shape.setRotation(rotation);
	this->shape.setPosition(cx - this->shape.getOutlineThickness(), cy - this->shape.getOutlineThickness());
}

void Grinder::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Grinder::levelUp()
{
	switch (this->level)
	{
	case 1:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(5.f, 5.f));
		this->rotation += 1;
		this->level++;
		break;
	case 2:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(5.f, 5.f));
		this->rotation += 1;
		this->level++;
		break;
	case 3:
		this->shape.setSize(this->shape.getSize() + sf::Vector2f(20.f, 20.f));
		this->rotation += 3;
		this->damage += 1.f;
		this->level++;
		break;
	default:
		break;
	}
}
