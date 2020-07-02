#include "inventory.h"
#include "../game_exception.h"

Inventory::Inventory(const int max_items) :
maxItems(max_items), numItems(0) {
    items.resize(maxItems);
}

Inventory::~Inventory() {
    for (auto& item : items)
        delete item;
}

void Inventory::checkFullness() {
    if (numItems == maxItems)
        throw GameException(0, "No tienes mas espacio en el inventario");
}

void Inventory::checkUniqueness(const int type) {
    for (auto& item : items)
        if (item->type == type)
            throw GameException(0, "Ya tienes este item en el inventario. "
                                   "Solo las pociones pueden tenerse mas "
                                   "de una vez");
}

void Inventory::addItem(Item* item) {
    checkFullness();

    if (item->uniqueInInventory)
        checkUniqueness(item->type);

    items.push_back(item);
    numItems ++;
}

Item* Inventory::removeItem(const int type) {
    size_t i;
    for (i = 0; i < items.size(); i ++) {
        if (items[i]->type == type) {
            Item* item = items[i];
            items.erase(items.begin() + i);
            numItems --;
            return item;
        }
    }
    return nullptr;
}
