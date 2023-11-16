#pragma once
/*
#include "Entity.h"
#include "GameState.h"
#include "stdafx.h"

class Inventory {
private:
    int xp;
    int gold;
    std::vector<std::string> items;

public:
    Inventory();
    ~Inventory();

    // Accessors
    int getXp() const;
    int getGold() const;
    const std::vector<std::string>& getItems() const;

    // Setter
    void setXp(int xp);
    void setGold(int gold);
    void addItem(const std::string& item);

    // Clear all items in the inventory
    void clearItems();
};
*/
class Inventory {
public:
    Inventory();
    ~Inventory();
};