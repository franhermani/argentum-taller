#ifndef ITEM_H
#define ITEM_H

class Item {
protected:
    int type{};
    int posX{}, posY{};

    // Actualiza la posicion (posX, posY) del item
    void updatePosition(const int new_x, const int new_y);

public:
    // Destructor
    virtual ~Item();
};

#endif // ITEM_H
