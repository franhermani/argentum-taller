#include "position_converter.h"

PositionConverter::PositionConverter(const int block_size) :
blockSize(block_size) {}

position_t PositionConverter::posToGranularPos(position_t pos) {
    position_t granular_pos(pos.x + blockSize/2, pos.y + blockSize/2);
    return granular_pos;
}

position_t PositionConverter::granularPosToPos(position_t granular_pos) {
    position_t pos(granular_pos.x / blockSize, granular_pos.y / blockSize);
    return pos;
}
