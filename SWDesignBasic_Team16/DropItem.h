#pragma once
#include "Inventory.h"

class DropItem {
private:

public:
    // Constructor
    DropItem(const sf::Vector2f& position, const Inventory& inventory, sf::Sprite* sprPtr = nullptr);
    DropItem(const sf::Vector2f& position, const Inventory& inventory, sf::Color color);
    sf::CircleShape shape;  // 작은 원 모양의 드랍 아이템
    sf::Sprite itemSprite;
    bool isSprite = false;

    // Accessors
    const sf::Vector2f& getPosition() const;
    // const Inventory& getInventory() const;

    // Draw the drop item
    void draw(sf::RenderTarget* target) const;
};