#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <vector>
#include <map>
#include "surface.h"
#include "area.h"

//SACAR ESTO DE ACA OBVIAMENTE

enum Terrain {
    TERRAIN_GRASS,
    TERRAIN_LAND,
    TERRAIN_SAND,
    TERRAIN_STONE,
    TERRAIN_WALL,
    TERRAIN_WATER,
};
enum Warrior {
    WARRIOR_UP,
    WARRIOR_DOWN,
    WARRIOR_RIGHT,
    WARRIOR_LEFT
};
enum Skeleton {
    SKELETON_UP,
    SKELETON_DOWN,
    SKELETON_RIGHT,
    SKELETON_LEFT
};


class SDL_Window;
class SDL_Surface;
class SDL_Renderer;

class SDLWindow {
    int width;
    int height;
    int blocks_width;
    int blocks_height;
    std::vector<std::vector<Terrain>> matrix;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    // Constructor
    SDLWindow(const int width, const int height);

    // Constructor y asignacion por copia deshabilitados
    SDLWindow(const SDLWindow &) = delete;

    SDLWindow &operator=(const SDLWindow &) = delete;

    // Destructor
    ~SDLWindow();

    // Colorea la pantalla segun el codigo RGB recibido
    void fill(const int r = 0, const int g = 0, const int b = 0,
              const int alpha = 255);

    // Renderiza la pantalla
    void render();

    // Devuelve el renderer
    SDL_Renderer *getRenderer() const;

    // Devuelve la surface de toda la ventana
    SDL_Surface *getSurface() const;

    // estampa en la ventana una surface con tamaño y posicion dado en area
    void stampSurface(Surface &surface, Area &area);

    // Devuelve el formato de la surface de la ventana
    SDL_PixelFormat *getSurfaceFormat() const;

    //Actualiza la ventana mostrada
    void UpdateWindowSurface();

    void render_terrain(std::map<int, SDL_Surface*> terrains_map);
};

#endif // SDL_WINDOW_H
