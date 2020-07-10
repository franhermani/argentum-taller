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
    Merchant(ItemFactory& item_factory, position_t new_pos, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Merchant(const Merchant& other) = delete;
    Merchant& operator=(const Merchant& other) = delete;

    // Destructor
    ~Merchant();

    // Lanza una excepcion
    void revive(Player& player) override;

    // Lanza una excepcion
    void heal(Player& player) override;

    // Compra un item al player segun 'item_type'
    void buyItem(Player& player, const int type) override;

    // Vende un item al player segun 'item_type'
    void sellItem(Player& player, const int type) override;

    // Lanza una excepcion
    void depositItem(Player& player, const int type) override;

    // Lanza una excepcion
    void withdrawItem(Player& player, const int type) override;

    // Lanza una excepcion
    void depositGold(Player& player, const int quant) override;

    // Lanza una excepcion
    void withdrawGold(Player& player, const int quant) override;

    // Lista los items que tiene para vender
    list_t listItems(Player& player) const override;
};

#endif // MERCHANT_H
