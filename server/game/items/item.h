#ifndef ITEM_H
#define ITEM_H

class Item {
protected:
    int type{};
    int posX{}, posY{};
    int price{};
    bool uniqueInInventory{};

    // Actualiza la posicion (posX, posY) del item
    void updatePosition(const int new_x, const int new_y);

    friend class World;
    friend class Player;
    friend class Inventory;

public:
    // Destructor
    virtual ~Item();
};

#endif // ITEM_H
