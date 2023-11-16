#include "Sword.h"

void Sword::initShape()
{
	MeleeWeapon::initShape();
	this->shape.setSize(sf::Vector2f(80.f, 80.f)); // ���⸶�� shape�� �޶����� ��ü������ �պ��ߵ�����
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

void Sword::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle)
{
	//swordPos.left = swordPos.left - (this->sword->shape.getGlobalBounds().width * 0.5f - 25);
	//swordPos.top = swordPos.top - (this->sword->shape.getGlobalBounds().height * 0.5f - 25);

	//this->sword->shape.setOrigin(-this->viewDirection.x * 50, -this->viewDirection.y * 50);
	sf::FloatRect pos;
	pos.left = cx - (this->shape.getGlobalBounds().width * 0.5f);
	pos.top = cy - (this->shape.getGlobalBounds().height * 0.5f);
	//this->shape.setRotation(angle);
	if (angle != 0.f) {
		this->shape.setPosition(cx - playerShape.getGlobalBounds().width * 0.5f, cy - playerShape.getGlobalBounds().height * 0.5f);
		this->shape.setOrigin(playerShape.getOrigin());
		// this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
		this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
		this->shape.setRotation(angle);
	}
	if (this->active && this->count >= this->duration * 60) {
		this->active = false;
		this->count = 0;
	}
	if (!this->active && this->count >= this->cooltime * 60) {
		this->active = true;
		this->count = 0;
	}

	this->count++;
}

void Sword::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

Sword::Sword(float cooltime, float damage, float duration) : MeleeWeapon(cooltime, damage, duration)
{
	initShape();
}

Sword::~Sword()
{
}