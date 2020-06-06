#include "area.h"

Area::Area(const int x, const int y, const int width, const int height) :
x(x), y(y), width(width), height(height) {}

const int Area::getX() const {
    return x;
}

const int Area::getY() const {
    return y;
}

const int Area::getWidth() const {
    return width;
}

const int Area::getHeight() const {
    return height;
}
