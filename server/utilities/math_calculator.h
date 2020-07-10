#ifndef MATH_H
#define MATH_H

class Math {
public:
    // Devuelve un numero entero aleatorio entre 'a' y 'b'
    const int randomInt(const int a, const int b);

    // Devuelve un numero double aleatorio entre 'a' y 'b'
    const double randomDouble(const double a, const double b);

    // Devuelve el promedio entre 'a' y 'b'
    const double average(const double a, const double b);
};

#endif // MATH_H
