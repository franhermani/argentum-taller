#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"

class Inventory {
    std::vector<Item*> items;

public:
    // Constructor
    explicit Inventory(const int num_items);

    // Constructor y asignacion por copia deshabilitados
    Inventory(const Inventory& other) = delete;
    Inventory& operator=(const Inventory& other) = delete;

    // Agrega un item al inventario
    void addItem(Item* item);

    // Saca un item del inventario segun su posicion
    Item* removeItem(const int pos);
};

#endif // INVENTORY_H
