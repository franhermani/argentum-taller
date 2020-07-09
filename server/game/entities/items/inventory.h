#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"

class Inventory {
    std::vector<Item*> items;
    int maxItems, numItems;

    // Lanza una excepcion si el inventario esta lleno
    void checkFullness();

    // Lanza una excepcion si el item type ya se encuentra en el inventario
    void checkUniqueness(const int type);

    friend class ServerProtocol;

public:
    // Constructor
    explicit Inventory(const int max_items);

    // Constructor y asignacion por copia deshabilitados
    Inventory(const Inventory& other) = delete;
    Inventory& operator=(const Inventory& other) = delete;

    // Destructor
    // Libera la memoria reservada para los items que esten almacenados
    ~Inventory();

    // Agrega un item al inventario
    // Lanza una excepcion si:
    // - el inventario esta lleno
    // - el item ya existia en el inventario y es de tipo unico,
    void addItem(Item* item);

    // Saca un item del inventario segun su item type
    Item* removeItem(const int type);

    // Saca el ultimo item del inventario
    Item* removeLastItem();

    // Elimina los items restantes del inventario
    // Es utilizado en caso de que no haya lugar en el mapa
    // para dropear los items al morir
    void deleteItems();

    // Devuelve true si el inventario esta vacio, false en caso contrario
    const bool isEmpty() const;
};

#endif // INVENTORY_H
