#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "item.h"

class ItemFactory {
public:
    // Constructor
    ItemFactory();

    // Constructor y asignacion por copia deshabilitados
    ItemFactory(const ItemFactory& other) = delete;
    ItemFactory& operator=(const ItemFactory& other) = delete;

    // Recibe un itemType y una pos(x,y) y devuelve una clase derivada de item
    Item* operator()(const int type, const int pos_x, const int pos_y);
};

#endif // ITEM_FACTORY_H
