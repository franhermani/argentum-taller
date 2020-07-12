#include <vector>
#include <algorithm>
#include <netinet/in.h>
#include "merchant.h"
#include "../../../../common/defines/npcs.h"
#include "../../game_exception.h"

Merchant::Merchant(ItemFactory& item_factory, position_t new_pos,
        const int orient, const int max_items) :
        itemFactory(item_factory), maxItems(max_items) {
    type = MERCHANT;
    pos = new_pos;
    orientation = orient;

    std::vector<int> all_items =
            {ESPADA, HACHA, MARTILLO, ARCO_SIMPLE, ARCO_COMPUESTO,
             ARMADURA_CUERO, ARMADURA_PLACAS, TUNICA_AZUL,
             CAPUCHA, CASCO_HIERRO, ESCUDO_TORTUGA, ESCUDO_HIERRO,
             POCION_VIDA, POCION_MANA};

    items = math.randomVector(all_items, maxItems);
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
    delete item;
}

void Merchant::sellItem(Player &player, int type) {
    if (std::find(items.begin(), items.end(), type) == items.end())
        return;

    Item* item = itemFactory(type, player.pos);
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

void Merchant::depositGold(Player &player) {
    throw GameException(player.id, "Un comerciante no tiene"
                                   "acceso al banco");
}

void Merchant::withdrawGold(Player &player) {
    throw GameException(player.id, "Un comerciante no tiene"
                                   "acceso al banco");
}

list_t Merchant::listItems(Player& player) const {
    int num_items = items.size();

    list_t list;
    list.show_price = 1;
    list.gold_quantity = 0;
    list.num_items = htons(num_items);
    list.items.resize(num_items);

    int i;
    for (i = 0; i < num_items; i ++) {
        list.items[i].type = items[i];
        list.items[i].price = htons(itemFactory.getItemPrice(items[i]));
    }
    return list;
}
