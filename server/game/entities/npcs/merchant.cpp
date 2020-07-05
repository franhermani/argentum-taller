#include <vector>
#include <algorithm>
#include "merchant.h"
#include "../../../../common/defines/npcs.h"
#include "../../game_exception.h"

Merchant::Merchant(ItemFactory& item_factory, const int pos_x,
        const int pos_y, const int orient) : itemFactory(item_factory) {
    type = MERCHANT;
    posX = pos_x;
    posY = pos_y;
    orientation = orient;

    items = {ESPADA, HACHA, MARTILLO, ARCO_SIMPLE, ARCO_COMPUESTO,
             ARMADURA_CUERO, ARMADURA_PLACAS, TUNICA_AZUL,
             CAPUCHA, CASCO_HIERRO, SOMBRERO_MAGICO,
             ESCUDO_TORTUGA, ESCUDO_HIERRO,
             POCION_VIDA, POCION_MANA};
}

Merchant::~Merchant() = default;

void Merchant::revive(Player &player) {
    throw GameException(player.id, "Un comerciante no tiene "
                                   "la habilidad de revivir al jugador");
}

void Merchant::heal(Player &player) {
    throw GameException(player.id, "Un comerciante no tiene "
                                   "la habilidad de curar al jugador");
}

void Merchant::buyItem(Player &player, int type) {
    Item* item = player.sellItem(type);
    if (! item)
        return;

    int item_type = item->type;
    if (std::find(items.begin(), items.end(), item_type) != items.end()) {
        items.push_back(item_type);
    }

    delete item;
}

void Merchant::sellItem(Player &player, int type) {
    if (std::find(items.begin(), items.end(), type) != items.end())
        return;

    Item* item = itemFactory(type, player.posX, player.posY);
    if (! item)
        return;

    player.buyItem(item);
}

void Merchant::depositItem(Player &player, const int type) {
    throw GameException(player.id, "Un comerciante no tiene"
                                   "acceso al banco");
}

void Merchant::withdrawItem(Player &player, const int type) {
    throw GameException(player.id, "Un comerciante no tiene"
                                   "acceso al banco");
}

void Merchant::depositGold(Player &player, const int quant) {
    throw GameException(player.id, "Un comerciante no tiene"
                                   "acceso al banco");
}

void Merchant::withdrawGold(Player &player, const int quant) {
    throw GameException(player.id, "Un comerciante no tiene"
                                   "acceso al banco");
}

const std::vector<int> Merchant::listItems() const {
    // TODO: ...
    return std::vector<int>();
}
