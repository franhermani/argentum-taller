#include "inventory.h"

Inventory::Inventory(const int max_items) :
maxItems(max_items), numItems(0) {
    items.resize(maxItems);
}

Inventory::~Inventory() {
    for (auto& item : items)
        delete item;
}

void Inventory::checkFullness() {
    // TODO: ...
//    if (numItems == maxItems) throw GamingException(code)
}

void Inventory::checkUniqueness(const int type) {
    // TODO: ...
//    for (auto& item : items)
//        if (item->type == type) throw GamingException(code)
}

void Inventory::addItem(Item* item) {
    checkFullness();
    if (item->uniqueInInventory) checkUniqueness(item->type);

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
    // TODO: throw GamingException(code);
    return nullptr;
}
