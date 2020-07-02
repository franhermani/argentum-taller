#include "item.h"

Item::~Item() = default;

void Item::updatePosition(const int new_x, const int new_y) {
    posX = new_x;
    posY = new_y;
}
