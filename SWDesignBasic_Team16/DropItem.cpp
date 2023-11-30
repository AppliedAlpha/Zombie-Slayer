#include "DropItem.h"

// Constructor
DropItem::DropItem(const sf::Vector2f& position, const Inventory& inventory, sf::Color color) {
    shape.setRadius(7.f);  // ���� ���� ������ ����
    shape.setPosition(position);
    shape.setFillColor(sf::Color(color));  // ������ ���÷� �Ķ���
}

// Accessors
const sf::Vector2f& DropItem::getPosition() const {
    return shape.getPosition();
}

void DropItem::draw(sf::RenderTarget* target) const
{
    target->draw(shape);
}