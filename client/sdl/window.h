#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "surface.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/items.h"
#include "area.h"
#include "window_measurements.h"

//SACAR ESTO DE ACA OBVIAMENTE

class SDL_Window;
class SDL_Surface;
class SDL_Renderer;

class SDLWindow {
    const int screenHeight;
    const int screenWidth;
    SDL_Window *window;
    SDL_Renderer *renderer;
    WindowMeasurements measurements;

    void renderExperience(std::map<int, float>& player_info,
                          std::map<int, Surface *> info_surfaces_map);

    void renderLife(std::map<int, float>& player_info,
                          std::map<int, Surface *> info_surfaces_map);

    void renderMana(std::map<int, float>& player_info,
                          std::map<int, Surface *> info_surfaces_map);



public:
    // Constructor
    SDLWindow(const int screenWidth, const int screenHeight);

    // Constructor y asignacion por copia deshabilitados
    SDLWindow(const SDLWindow &) = delete;

    SDLWindow &operator=(const SDLWindow &) = delete;

    // Destructor
    ~SDLWindow();

    //inicializa areas estaticas donde se renderizara
    void initializeStaticAreas();

    // Colorea la pantalla segun el codigo RGB recibido
    void fill(const int r = 0, const int g = 0, const int b = 0,
              const int alpha = 255);

    // Renderiza la pantalla
    void render();

    // Devuelve el renderer
    SDL_Renderer *getRenderer() const;

    // Devuelve la surface de toda la ventana
    SDL_Surface *getSurface() const;

    // Devuelve el formato de la surface de la ventana
    SDL_PixelFormat *getSurfaceFormat() const;

    //Actualiza la ventana mostrada
    void UpdateWindowSurface();

    // Configura la cantidad de bloques recibida del sevidor
    void setTilesSize(int tileWidth, int tileHeight);

    // Conversores de metrica del juego a pixel
    int getXPixelPos(int x_tile_position);
    int getYPixelPos(int y_tile_position);

    //renderizadores dentro de la pantalla del mapa
    void renderTerrain(std::vector<std::vector<Terrain>> &matrix,
            std::map<Terrain, Surface *> &surfaces_map);
    void renderMapObject(int x, int y, Surface *character_surface);

    //renderizadores marco + lo que contiene
    void renderGameFrame(Surface *surface);
    void renderInventory(std::vector<uint8_t>& inventory,
            std::map<int,Surface*>& surfaces);
    void renderEquipped(player_t& player,
            std::map<int, Surface*>& surfaces_map);
    void renderPlayerInfo(std::map<int, float>& player_info,
            std::map<int, Surface *> info_surfaces_map);
    void renderList(std::vector<Surface*>& surfaces);
    void renderListGold(Surface* surface);
    void renderInventoryGolds(Surface* surface);


    //Consultas a elementos o sectores renderizados
    int getRenderedItemIndexByPosition(int x, int y, size_t inventory_length);
    int getRenderedListIndexByPosition(int x, int y, size_t inventory_length);
    int isInsideArea(SDL_Rect& stretchRect, int x, int y);
    int isInsideGameArea(game_area_t& area, int x, int y);
    int isClickingListItems(int x, int y);
    int isClickingListGold(int x, int y);
    int isClickingInventoryItems(int x, int y);
    int isClickingInventoryGold(int x, int y);
    };
#endif // SDL_WINDOW_H
