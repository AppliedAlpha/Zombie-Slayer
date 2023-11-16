#include "DropItem.h"

// Constructor
DropItem::DropItem(const sf::Vector2f& position, const Inventory& inventory) : inventory(inventory) {
    shape.setRadius(10.f);  // ���� ���� ������ ����
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);  // ������ ���÷� �Ķ���
}

// Accessors
const sf::Vector2f& DropItem::getPosition() const {
    return shape.getPosition();
}

const Inventory& DropItem::getInventory() const {
    return inventory;
}

// Draw the drop item
void DropItem::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}
