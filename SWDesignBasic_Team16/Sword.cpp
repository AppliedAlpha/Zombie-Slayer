#include "Sword.h"

void Sword::initShape()
{
	MeleeWeapon::initShape();
	this->shape.setSize(sf::Vector2f(45.f, 45.f)); // 무기마다 shape가 달라지면 전체적으로 손봐야도리듯
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setOutlineThickness(2.f);

	/*this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);*/
	// this->shape.setOrigin(50, 50);
}

void Sword::updateCollision(Entity* object)
{
}

void Sword::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection)
{
	MeleeWeapon::update(dt, playerShape, cx, cy, viewDirection);
	//swordPos.left = swordPos.left - (this->sword->shape.getGlobalBounds().width * 0.5f - 25);
	//swordPos.top = swordPos.top - (this->sword->shape.getGlobalBounds().height * 0.5f - 25);
	//this->sword->shape.setOrigin(-this->viewDirection.x * 50, -this->viewDirection.y * 50);
	float angle = this->getViewAngle(viewDirection);
	// this->shape.setRotation(angle);
	if (angle != 0.f) {
		this->shape.setPosition(cx - playerShape.getGlobalBounds().width * 0.5f, cy - playerShape.getGlobalBounds().height * 0.5f);
		this->shape.setOrigin(playerShape.getOrigin());
		// this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
		this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
		this->shape.setRotation(angle);
	}
}

void Sword::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

Sword::Sword(float cooltime, float damage, float duration, sf::Vector2f position) : MeleeWeapon(cooltime, damage, duration, position)
{
	initShape();
}

Sword::~Sword()
{
};