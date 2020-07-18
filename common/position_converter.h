#ifndef ARGENTUM_POSITION_CONVERTER_H
#define ARGENTUM_POSITION_CONVERTER_H

#include "defines/position.h"

class PositionConverter {
    int blockSize;

public:
    // Constructor
    explicit PositionConverter(const int block_size);

    // Constructor y asignacion por copia deshabilitados
    PositionConverter(const PositionConverter& other) = delete;
    PositionConverter& operator=(const PositionConverter& other) = delete;

    // Convierte una posicion entera a granular
    position_t posToGranularPos(position_t pos);

    // Convierte una posicion granular a entera
    position_t granularPosToPos(position_t granular_pos);
};

#endif // POSITION_CONVERTER_H
