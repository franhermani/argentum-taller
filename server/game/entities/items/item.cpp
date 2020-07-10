#include "item.h"

Item::~Item() = default;

void Item::updatePosition(position_t new_pos) {
    pos = new_pos;
}
