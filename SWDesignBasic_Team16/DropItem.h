#pragma once
#include "Inventory.h"

class DropItem {
private:

public:
    // Constructor
    DropItem(const sf::Vector2f& position, const Inventory& inventory, sf::Color color);
    sf::CircleShape shape;  // ���� �� ����� ��� ������
    // Accessors
    const sf::Vector2f& getPosition() const;
    // const Inventory& getInventory() const;

    // Draw the drop item
    void draw(sf::RenderTarget* target) const;
};