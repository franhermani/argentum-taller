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
    void revive(Player& player);

    // Cura al player
    void heal(Player& player);

    // Vende un item al player segun 'item_type'
    void sellItem(Player& player, const int type);

    // Lista los items que tiene para vender
    const std::vector<int> listItems() const override;
};

#endif // PRIEST_H
