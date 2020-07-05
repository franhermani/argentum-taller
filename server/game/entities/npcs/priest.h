#ifndef PRIEST_H
#define PRIEST_H

#include <vector>
#include "npc.h"
#include "../items/item_factory.h"
#include "../living_beings/player.h"

class Priest : public NPC {
    ItemFactory& itemFactory;

public:
    // Constructor
    Priest(ItemFactory& item_factory, const int pos_x,
            const int pos_y, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Priest(const Priest& other) = delete;
    Priest& operator=(const Priest& other) = delete;

    // Destructor
    ~Priest();

    // Revive al player
    void revive(Player& player) override;

    // Cura al player
    void heal(Player& player) override;

    // Lanza una excepcion
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

#endif // PRIEST_H
