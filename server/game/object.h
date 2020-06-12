#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
protected:
    int id;
    int posX, posY;
    bool isImpenetrable;

    friend class World;
};

#endif // GAME_OBJECT_H
