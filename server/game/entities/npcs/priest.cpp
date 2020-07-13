#include <vector>
#include <netinet/in.h>
#include "priest.h"
#include "../../../../common/defines/npcs.h"
#include "../../../../common/defines/commands.h"
#include "../../game_exception.h"

Priest::Priest(ItemFactory& item_factory, position_t new_pos) :
itemFactory(item_factory) {
    type = PRIEST;
    pos = new_pos;
    orientation = DOWN;

    items = {VARA_FRESNO, FLAUTA_ELFICA, BACULO_NUDOSO, BACULO_ENGARZADO,
             POCION_VIDA, POCION_MANA};
}

Priest::~Priest() = default;

void Priest::revive(Player &player) {
    player.shortTermRevive();
}

void Priest::heal(Player &player) {
    player.heal();
}

void Priest::buyItem(Player &player, int type) {
    throw GameException(player.id, "Un sacerdote no puede "
                                   "comprar items");
}

void Priest::sellItem(Player &player, const int type) {
    if (std::find(items.begin(), items.end(), type) == items.end())
        return;

    Item* item = itemFactory(type, player.pos);
    if (! item)
        return;

    player.buyItem(item);
}

void Priest::depositItem(Player &player, const int type) {
    throw GameException(player.id, "Un sacerdote no tiene"
                                   "acceso al banco");
}

void Priest::withdrawItem(Player &player, const int type) {
    throw GameException(player.id, "Un sacerdote no tiene"
                                   "acceso al banco");
}

void Priest::depositGold(Player &player) {
    throw GameException(player.id, "Un sacerdote no tiene"
                                   "acceso al banco");
}

void Priest::withdrawGold(Player &player) {
    throw GameException(player.id, "Un sacerdote no tiene"
                                   "acceso al banco");
}

list_t Priest::listItems(Player& player) const {
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
