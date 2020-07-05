#include <vector>
#include "priest.h"
#include "../../../../common/defines/npcs.h"
#include "../../../../common/defines/items.h"

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

void Priest::sellItem(Player &player, const int type) {
    if (items.count(type) == 0)
        return;

    Item* item = itemFactory(type, player.posX, player.posY);
    if (! item)
        return;

    player.buyItem(item);
}

const std::vector<itemType> Priest::listItems() const {
    return std::vector<itemType>();
}
