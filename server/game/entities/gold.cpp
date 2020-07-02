#include "gold.h"

Gold::Gold(const int quantity, const int pos_x, const int pos_y) :
quantity(quantity), posX(pos_x), posY(pos_y) {}

void Gold::updatePosition(const int new_x, const int new_y) {
    posX = new_x;
    posY = new_y;
}
