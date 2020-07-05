#ifndef MERCHANT_H
#define MERCHANT_H

#include <vector>
#include "npc.h"
#include "../living_beings/player.h"

class Merchant : public NPC {
public:
    // Constructor
    Merchant(const int pos_x, const int pos_y, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Merchant(const Merchant& other) = delete;
    Merchant& operator=(const Merchant& other) = delete;

    // Destructor
    ~Merchant();

    // Compra el item al player
    void buy(Player& player, int item_type);

    // Vende el item al player
    void sell(Player& player, int item_type);

    // Lista los items que tiene para vender
    const std::vector<itemType> listItems() const override;
};

#endif // MERCHANT_H
