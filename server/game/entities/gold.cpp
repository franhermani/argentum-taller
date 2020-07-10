#include "gold.h"

Gold::Gold(const int quantity, position_t new_pos) :
quantity(quantity), pos(new_pos) {}

void Gold::updatePosition(position_t new_pos) {
    pos = new_pos;
}
