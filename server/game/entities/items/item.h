#ifndef ITEM_H
#define ITEM_H

#include "../../../../common/defines/position.h"

class Item {
protected:
    int type{};
    position_t pos{};
    int price{};
    bool uniqueInInventory{};

    // Actualiza la posicion (posX, posY) del item
    void updatePosition(position_t new_pos);

    friend class World;
    friend class Player;
    friend class Inventory;
    friend class Bank;
    friend class Banker;
    friend class Merchant;
    friend class ServerProtocol;

public:
    // Destructor
    virtual ~Item();
};

#endif // ITEM_H
