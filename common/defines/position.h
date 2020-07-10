#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include <stdlib.h>

struct position_t {
    uint16_t x;
    uint16_t y;

    // Constructor sin parametros
    position_t() = default;

    // Constructor con parametros
    position_t(uint16_t x, uint16_t y) : x(x), y(y) {}

    // Asignacion por copia
    position_t& operator=(const position_t& other) {
        if (&other == this)
            return *this;
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    // Comparacion
    bool operator==(const position_t& other) const {
        return (x == other.x) && (y == other.y);
    }

    // Distancia
    const int distance(const position_t& other) const {
        int dist_x = abs(x - other.x), dist_y = abs(y - other.y);
        return dist_x + dist_y;
    }
};

#endif // POSITION_H
