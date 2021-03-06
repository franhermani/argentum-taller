#ifndef MATH_H
#define MATH_H

#include <vector>
#include "position.hpp"

class Math {
public:
    // Devuelve un numero entero aleatorio entre 'a' y 'b'
    const int randomInt(const int a, const int b);

    // Devuelve un numero double aleatorio entre 'a' y 'b'
    const double randomDouble(const double a, const double b);

    // Devuelve un sub-vector random de largo n del vector recibido
    std::vector<int> randomVector(const std::vector<int>& v, const int n);

    // Devuelve una posicion aleatoria segun el vector recibido
    position_t randomPosition(const std::vector<position_t>& p);

    // Devuelve el promedio entre 'a' y 'b'
    const double average(const double a, const double b);
};

#endif // MATH_H
