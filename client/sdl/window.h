#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "surface.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/items.h"
#include "../../common/defines/commands.h"
#include "window_measurements.h"


class SDL_Window;
class SDL_Surface;

class SDLWindow {
    int screenHeight;
    int screenWidth;
    int fullscreen;
    SDL_Window *window;
    WindowMeasurements measurements;


    // Calculadores de rects
    SDL_Rect calculateMapObjectRect(int x, int y);
    int isOutsideFrameArea(SDL_Rect& stretch_rect, game_area_t& frame_area);
    SDL_Rect calculateInventoryStartRect();
    SDL_Rect calculateEquippedStartRect();
    SDL_Rect calculateListStartRect(game_area_t& list_area);

    // Renderizadores auxiliares internos de la clase
    void renderInfoBar(Surface * bar, Surface* background,
            game_area_t& area, float percentage);
    void renderListArea(game_area_t& list_area,
            std::vector<Surface*>& surfaces);
    void renderEqIfExists(std::map<int, Surface*>& surfaces_map,
                          SDL_Rect& rect, int item);

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

    // activa/desactiva pantalla completa
    void toggleFullscreen();


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

    void renderMapObject(int x, int y, Surface *character_surface);
    void renderAnimatedMapObject(int x, int y, Surface *character_surface,
            int iteration);
    void renderMapObjectLifeBar(int x, int y, Surface* bar, float percentage);

    //renderizadores marco + lo que contiene
    void renderGameFrame(Surface *surface);
    void renderInventory(std::vector<uint8_t>& inventory,
            std::map<int,Surface*>& surfaces);
    void renderEquipped(player_t& player,
            std::map<int, Surface*>& surfaces_map);
    void renderPlayerInfo(std::map<int, float>& player_info,
            std::map<int, Surface *>& info_surfaces_map,
            Surface* level_surface, Surface* name_surface);
    void renderList(std::vector<Surface*>& surfaces);
    void renderListPrices(std::vector<Surface*>& surfaces);
    void renderListGold(Surface* surface, Surface* quantity);
    void renderInventoryGolds(Surface* surface, Surface* quantity);
    void renderLevel(Surface* level_surface);
    void renderName(Surface* name_surface);
    void renderWorld(Surface* surface, position_t positon,
                     int dimensions_width, int dimensions_height);


        //Consultas a elementos o sectores renderizado
    SDL_Rect getFrameRectByPosition(Surface* surface, position_t position,
        int dimensions_width, int dimensions_height);
    int getRenderedItemIndexByPosition(int x, int y, size_t inventory_length);
    int getRenderedListIndexByPosition(int x, int y, size_t inventory_length);
    int getRenderedEquipedTypeByPosition(int x, int y);
    int isInsideArea(SDL_Rect& stretchRect, int x, int y);
    int isInsideGameArea(game_area_t& area, int x, int y);
    int isClickingListItems(int x, int y);
    int isClickingListGold(int x, int y);
    int isClickingInventoryItems(int x, int y);
    int isClickingInventoryGold(int x, int y);
    };
#endif // SDL_WINDOW_H
