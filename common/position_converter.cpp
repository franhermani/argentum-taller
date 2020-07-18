#include "position_converter.h"

PositionConverter::PositionConverter(const int block_size) :
blockSize(block_size) {}

position_t PositionConverter::posToGranularPos(position_t pos) {
    position_t granular_pos{};
    granular_pos.x = pos.x * blockSize + blockSize/2;
    granular_pos.y = pos.y * blockSize + blockSize/2;
    return granular_pos;
}

position_t PositionConverter::granularPosToPos(position_t granular_pos) {
    position_t pos{};
    pos.x = granular_pos.x / blockSize;
    pos.y = granular_pos.y / blockSize;
    return pos;
}
