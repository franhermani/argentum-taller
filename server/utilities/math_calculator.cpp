#include <random>
#include "math_calculator.h"

const int Math::randomInt(const int a, const int b) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(a, b);
    return dist(mt);
}

const double Math::randomDouble(const double a, const double b) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(mt);
}

const double Math::average(const double a, const double b) {
    return (a + b)/2;
}
