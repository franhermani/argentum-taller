#ifndef SDL_AREA_H
#define SDL_AREA_H

class Area {
    int x;
    int y;
    int width;
    int height;

public:
    // Constructor
    Area(const int x, const int y, const int width, const int height);

    // Constructor y asignacion por copia deshabilitados
    Area(const Area&) = delete;
    Area& operator=(const Area&) = delete;

    // Devuelve el atributo 'x'
    const int getX() const;

    // Devuelve el atributo 'y'
    const int getY() const;

    // Devuelve el atributo 'width'
    const int getWidth() const;

    // Devuelve el atributo 'height'
    const int getHeight() const;
};

#endif // SDL_AREA_H
