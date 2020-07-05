#include <vector>
#include <algorithm>
#include "merchant.h"
#include "../../../../common/defines/npcs.h"

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

const std::vector<int> Merchant::listItems() const {
    // TODO: ...
    return std::vector<int>();
}
