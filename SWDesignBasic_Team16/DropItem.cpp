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
    if (this->isSprite)
        target->draw(itemSprite);
    else
        target->draw(shape);
}