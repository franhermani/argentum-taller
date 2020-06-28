#ifndef MERCHANT_H
#define MERCHANT_H

#include "npc.h"
#include "../player.h"

class Merchant : public NPC {
public:
    // Constructor
    Merchant(const int pos_x, const int pos_y, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Merchant(const Merchant& other) = delete;
    Merchant& operator=(const Merchant& other) = delete;

    // Destructor
    ~Merchant();

    // Compra un item al player recibido
    void buy(Player& player, int item_type);

    // Vende un item al player recibido
    void sell(Player& player, int item_type);
};

#endif // MERCHANT_H
