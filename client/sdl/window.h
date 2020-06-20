#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "surface.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npcs.h"
#include "area.h"

//SACAR ESTO DE ACA OBVIAMENTE

class SDL_Window;
class SDL_Surface;
class SDL_Renderer;

class SDLWindow {
    int numberOfTilesInWidth;
    int numberOfTilesInHeight;
    int xWidthTileSize;
    int yHeightTileSize;
    int width;
    int height;
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

    // Convierte posicion en eje X a pixel de la pantalla
    int getXPixelPos(int x_tile_position);

    // Converite posicion en eje Y a pixel de la pantalla
    int getYPixelPos(int y_tile_position);

    // Renderiza los pisos
    void renderTerrain(std::vector<std::vector<Terrain>> &matrix,
                       std::map<Terrain, Surface *> &surfaces_map);

    // Renderiza npcs
    void renderNpc(int x, int y, Surface *character_surface);

    void setTilesSize(int width, int height);
};

#endif // SDL_WINDOW_H
