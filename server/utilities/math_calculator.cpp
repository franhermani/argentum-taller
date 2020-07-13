#include <vector>
#include <random>
#include <algorithm>
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

std::vector<int> Math::randomVector(const std::vector<int> &v, const int n) {
    std::vector<int> random_v = v;
    std::random_shuffle(random_v.begin(), random_v.end());
    return std::vector<int>(random_v.begin(), random_v.begin() + n);
}

position_t Math::randomPosition(const std::vector<position_t>& p) {
    int index = randomInt(0, p.size());
    return p[index];
}

const double Math::average(const double a, const double b) {
    return (a + b)/2;
}
