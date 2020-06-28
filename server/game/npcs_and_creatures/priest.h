#ifndef PRIEST_H
#define PRIEST_H

#include "npc.h"
#include "../player.h"

class Priest : public NPC {
public:
    // Constructor
    Priest(const int pos_x, const int pos_y, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Priest(const Priest& other) = delete;
    Priest& operator=(const Priest& other) = delete;

    // Destructor
    ~Priest();

    // Revive al player
    void revive(Player& player);

    // Cura al player
    void heal(Player& player);
};

#endif // PRIEST_H
