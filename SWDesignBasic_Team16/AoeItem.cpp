#include "AoeItem.h"

AoeItem::AoeItem(float cooltime, float damage, float duration, sf::Vector2f position) : Item(cooltime, damage, duration, position)
{
	this->shape.setPosition(position);
}

AoeItem::~AoeItem()
{
}

void AoeItem::initShape()
{
}

void AoeItem::updateCollision(Entity* object)
{
}

void AoeItem::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy)
{
	Item::update(dt, playerShape, cx, cy);
}

void AoeItem::render(sf::RenderTarget* target)
{
}
