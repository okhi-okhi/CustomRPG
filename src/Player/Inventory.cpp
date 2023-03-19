#include "Inventory.h"
#include <iostream>
#include "../I18n/I18n.h"
#include "../System/Exceptions.hpp"

int Inventory::getItemSlot(const Item & item) const {
    for (int idx = 0; idx < this->items.size(); ++idx){
        if (items[idx].first->getId() == item.getId() && items[idx].first->getRarity() == item.getRarity()){
            return idx;
        }
    }
    return -1;
}

std::pair<Item*, int> Inventory::operator[](const int index) const
{
    if (index < 0 || index >= this->itemNums) {
        throw OutOfRangeException(index, this->itemNums);
    }

    return this->items[index];
}

void Inventory::addItem(Item& item) {
    addItem(item, 1);
}

void Inventory::addItem(Item& item, const int amount) {
    if (amount < 1) {
        throw InvBadAmountException(amount);
    }
    if (item.isStackable()){
        const int slot = this->getItemSlot(item);
	    if (slot != -1) {
            this->items[slot].second += amount;
        }
        else {
            this->items.emplace_back(&item, amount);
            this->itemNums++;
        }
    }
    else {
        for (int i = 0; i < amount; i++) {
            this->items.emplace_back(&item, 1);
            this->itemNums++;
        }
    }
}

bool Inventory::removeItem(const std::string& id) {
    return removeItem(id, 1);
}

bool Inventory::removeItem(const std::string& id, const int amount) {
    if (amount < 1) {
        throw InvBadAmountException(amount);
    }
    int i = 0, j = amount;
	for (const auto& fst : items | std::views::keys) {
		if(fst->getId() == id) {
            if(fst->isStackable()) {
                return removeItem(i, amount);
            }
			j--;
			if(j == 0) {
				break;
            }
		}
        i++;
	}
    if(j > 0) {
        return false;
    }
    for (i = 0; i < this->itemNums;) {
        if (items[i].first->getId() == id) {
            removeItem(i);
            j++;
        }
        else {
            i++;
        }
        if(j == amount) {
            break;
        }
    }
    return true;
}

bool Inventory::removeItem(const int index) {
    return removeItem(index, 1);
}

bool Inventory::removeItem(const int index, const int amount)
{
    if (index < 0 || index >= this->itemNums) {
        throw OutOfRangeException(index, this->itemNums);
    }
    if (amount < 1) {
        throw InvBadAmountException(amount);
    }

    if(this->items[index].second < amount) {
        return false;
    }
    else if(this->items[index].second == amount) {
        items.erase(items.begin() + index);
        this->itemNums--;
        return true;
    }
    else {
        this->items[index].second -= amount;
        return true;
    }
}

void Inventory::print() const {
    using std::cout, std::endl, std::to_string;
    for (const auto& [fst, snd] : this->items) {
        fst->print();
        cout << I18n::instance().get("player.inventory.print.name", { {"name", fst->getName()} }) << endl;
        cout << I18n::instance().get("player.inventory.print.id", { {"id", fst->getId()} }) << endl;
        cout << I18n::instance().get("player.inventory.print.amount", { {"amount", to_string(snd)} }) << endl;
    }
}