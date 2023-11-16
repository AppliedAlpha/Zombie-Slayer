#pragma once

#include "Inventory.h"

using namespace sf;

class DropItem {
private:
    CircleShape shape;  // 작은 원 모양의 드랍 아이템
    Inventory inventory;    // 드랍되는 인벤토리

public:
    // Constructor
    DropItem(const Vector2f& position, const Inventory& inventory);

    // Accessors
    const Vector2f& getPosition() const;
    const Inventory& getInventory() const;

    // Draw the drop item
    void draw(RenderWindow& window) const;
};
