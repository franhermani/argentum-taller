#ifndef LIVING_OBJECT_H
#define LIVING_OBJECT_H

#include "game_object.h"

class LivingObject : public GameObject {
protected:
    int actualLife, maxLife;
    int posX, posY;
    bool isImpenetrable;

public:
    // Mueve al personaje segun la direccion dada
    // Metodo a definir por las clases derivadas
    virtual void moveTo(int direction) = 0;
};

#endif // LIVING_OBJECT_H
