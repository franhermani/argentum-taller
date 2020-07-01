#ifndef BANK_H
#define BANK_H

#include <mutex>
#include <vector>
#include <map>
#include "items/item.h"

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
    void depositItem(const int id, Item* item);

    // Retira el item segun su type de las pertenencias del player segun su id
    Item* withdrawItem(const int id, const int type);

    // Agrega la cantidad de oro al oro del player segun su id
    void depositGold(const int id, const int quant);

    // Retira la cantidad de oro del player segun su id
    void withdrawGold(const int id, const int quant);
};

#endif // BANK_H
