#include <vector>
#include "priest.h"
#include "../../../../common/defines/npcs.h"
#include "../../game_exception.h"

Priest::Priest(ItemFactory& item_factory, const int pos_x, const int pos_y,
        const int orient) : itemFactory(item_factory) {
    type = PRIEST;
    posX = pos_x;
    posY = pos_y;
    orientation = orient;

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
    if (std::find(items.begin(), items.end(), type) != items.end())
        return;

    Item* item = itemFactory(type, player.posX, player.posY);
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

void Priest::depositGold(Player &player, const int quant) {
    throw GameException(player.id, "Un sacerdote no tiene"
                                   "acceso al banco");
}

void Priest::withdrawGold(Player &player, const int quant) {
    throw GameException(player.id, "Un sacerdote no tiene"
                                   "acceso al banco");
}

const std::vector<int> Priest::listItems() const {
    return std::vector<int>();
}
