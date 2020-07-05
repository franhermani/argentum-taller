#ifndef MERCHANT_H
#define MERCHANT_H

#include <vector>
#include "npc.h"
#include "../living_beings/player.h"
#include "../items/item_factory.h"

class Merchant : public NPC {
    ItemFactory& itemFactory;

public:
    // Constructor
    Merchant(ItemFactory& item_factory, const int pos_x,
            const int pos_y, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Merchant(const Merchant& other) = delete;
    Merchant& operator=(const Merchant& other) = delete;

    // Destructor
    ~Merchant();

    // Compra un item al player segun 'item_type'
    void buyItem(Player& player, int item_type);

    // Vende un item al player segun 'item_type'
    void sellItem(Player& player, int item_type);

    // Lista los items que tiene para vender
    const std::vector<int> listItems() const override;
};

#endif // MERCHANT_H
