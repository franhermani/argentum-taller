
#ifndef ARGENTUM_WINDOW_MEASUREMENTS_H
#define ARGENTUM_WINDOW_MEASUREMENTS_H

#include <SDL2/SDL_rect.h>
#include "render_structs.h"


struct WindowMeasurements {
    int numberOfTilesInWidth;
    int numberOfTilesInHeight;
    int xWidthTileSize;
    int yHeightTileSize;
    int screenHeight;
    int screenWidth;
    game_area_t frame;
    game_area_t inventory;
    game_area_t inventoryGold;
    game_area_t list;
    game_area_t list_prices;
    game_area_t listGold;
    game_area_t equipped;
    game_area_t life;
    game_area_t mana;
    game_area_t experience;
    game_area_t level;
    game_area_t name;

    SDL_Rect levelStaticRect;
    SDL_Rect nameStaticRect;
    SDL_Rect worldStaticRect;
    SDL_Rect gameFrameStaticRect;
    SDL_Rect inventoryGoldStaticRect;
    SDL_Rect listGoldStaticRect;
    SDL_Rect listGoldQuantityStaticRect;
    WindowMeasurements();
    ~WindowMeasurements();

    //inicializa medidas de los elementos a renderizar. Dura toda la ejecucion
    void initialize(int numberOfTilesInWidth, int numberOfTilesInHeight,
                    int screenWidth, int screenHeight);
    void updateResolution(int width, int height);
    
private:
    void initializePlayerInfo(int screenWidth, int screenHeight);
    void initializeItemInfo(int screenWidth, int screenHeight);
    void initializeStaticAreas();
    };


#endif //ARGENTUM_WINDOW_MEASUREMENTS_H
