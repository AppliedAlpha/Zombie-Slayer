#include "DropItem.h"

// Constructor
DropItem::DropItem(const sf::Vector2f& position, const Inventory& inventory) : inventory(inventory) {
    shape.setRadius(10.f);  // 작은 원의 반지름 설정
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);  // 색상은 예시로 파란색
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
