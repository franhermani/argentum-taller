#include "inventory.h"

Inventory::Inventory(const int num_items) {
    items.resize(num_items);
}

void Inventory::addItem(Item* item) {
    items.push_back(item);
}

Item* Inventory::removeItem(const int pos) {
    Item* item = items[pos];
    items.erase(items.begin() + pos);
    return item;
}
