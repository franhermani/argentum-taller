#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "surface.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npc.h"
#include "area.h"

//SACAR ESTO DE ACA OBVIAMENTE

class SDL_Window;
class SDL_Surface;
class SDL_Renderer;

class SDLWindow {
    int width;
    int height;
    int blocks_width;
    int blocks_height;
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

    // ...
    void renderTerrain(std::vector<std::vector<Terrain>>& matrix,
            std::map<Terrain, Surface&>& surfaces_map);

    // ...
    void renderNpc(int x, int y, Surface& character_surface);
};

#endif // SDL_WINDOW_H
