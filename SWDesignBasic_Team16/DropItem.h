#pragma once

#include "Inventory.h"

using namespace sf;

class DropItem {
private:
    CircleShape shape;  // ���� �� ����� ��� ������
    Inventory inventory;    // ����Ǵ� �κ��丮

public:
    // Constructor
    DropItem(const Vector2f& position, const Inventory& inventory);

    // Accessors
    const Vector2f& getPosition() const;
    const Inventory& getInventory() const;

    // Draw the drop item
    void draw(RenderWindow& window) const;
};
