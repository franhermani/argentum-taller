#include "punch.h"

Punch::Punch(Player* player, const int pos_x, const int pos_y,
        const int direction) : player(player), posX(pos_x), posY(pos_y),
        direction(direction), range(1) {}
