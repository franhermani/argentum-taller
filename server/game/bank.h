#ifndef BANK_H
#define BANK_H

#include <mutex>
#include <vector>
#include <map>
#include "entities/items/item.h"

class Bank {
    std::mutex m;
    std::map<int, std::vector<Item*>> itemsPerPlayer;
    std::map<int, int> goldPerPlayer;

public:
    // Constructor
    Bank();

    // Constructor y asignacion por copia deshabilitados
    Bank(const Bank& other) = delete;
    Bank& operator=(const Bank& other) = delete;

    // Destructor
    // Libera la memoria reservada para los items guardados en el banco
    ~Bank();

    // Agrega el item a las pertenencias del player segun su id
    void depositItem(const int player_id, Item* item);

    // Retira el item segun su type de las pertenencias del player segun su id
    Item* withdrawItem(const int player_id, const int type);

    // Agrega la cantidad de oro al oro del player segun su id
    void depositGold(const int player_id, const int quant);

    // Retira la cantidad de oro del player segun su id
    void withdrawGold(const int player_id, const int quant);

    // Devuelve los items que tiene el player en el banco
    // Si no tiene nada, devuelve un vector vacio
    std::vector<Item*> getItems(const int player_id);

    // Devuelve la cantidad de oro que tiene el player en el banco
    // Si no tiene nada, devuelve cero
    const int getGoldQuantity(const int player_id);
};

#endif // BANK_H
