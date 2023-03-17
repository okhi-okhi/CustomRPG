#pragma once
#include "../Item/Item.h"

class Inventory
{
private:
    std::vector<std::pair<Item*, int>> items;
    int itemNums = 0;

    int getItemSlot(const Item& item) const;

public:
    Inventory() = default;

    std::pair<Item*, int> operator[](int index) const;
    
    void addItem(Item& item);
    void addItem(Item& item, int amount);

    bool removeItem(const std::string& id);
    bool removeItem(const std::string& id, int amount);
    bool removeItem(int index);
    bool removeItem(int index, int amount);

    void print() const;

    int getSize() const { return static_cast<int>(this->items.size()); }
};

