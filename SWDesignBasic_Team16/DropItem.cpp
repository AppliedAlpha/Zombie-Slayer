#include "DropItem.h"

DropItem::DropItem(const sf::Vector2f& position, const Inventory& inventory, sf::Sprite* sprPtr) {
    this->shape.setRadius(8.f);
    this->shape.setPosition(position);
    
    if (sprPtr != nullptr) {
        this->isSprite = true;

        this->itemSprite = *sprPtr; // sf::Sprite(*sprPtr);
        this->itemSprite.setPosition(position);
    }
}

// Constructor
DropItem::DropItem(const sf::Vector2f& position, const Inventory& inventory, sf::Color color) {
    shape.setRadius(7.f);  // 작은 원의 반지름 설정
    shape.setPosition(position);
    shape.setFillColor(sf::Color(color));  // 색상은 예시로 파란색
}

// Accessors
const sf::Vector2f& DropItem::getPosition() const {
    return shape.getPosition();
}

void DropItem::draw(sf::RenderTarget* target) const
{
    if (this->isSprite)
        target->draw(itemSprite);
    else
        target->draw(shape);
}