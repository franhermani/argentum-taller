#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include <string>
#include <map>
#include <set>
#include "item.h"
#include "../../../utilities/json.hpp"

using json = nlohmann::json;

class ItemFactory {
    json itemParams;
    std::map<int, std::string> itemsMap;
    std::map<std::string, int> attackTypesMap;
    std::set<int> weapons;
    std::set<int> armors;
    std::set<int> helmets;
    std::set<int> shields;
    std::set<int> potions;

public:
    // Constructor
    explicit ItemFactory(json item_params);

    // Constructor y asignacion por copia deshabilitados
    ItemFactory(const ItemFactory& other) = delete;
    ItemFactory& operator=(const ItemFactory& other) = delete;

    // Recibe un itemType y una pos(x,y) y devuelve una clase derivada de item
    Item* operator()(const int type, position_t new_pos);

    // Devuelve el precio asociado a un item segun 'type'
    const int getItemPrice(const int type);
};

#endif // ITEM_FACTORY_H
