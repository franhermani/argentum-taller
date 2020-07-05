
#ifndef ARGENTUM_WINDOW_MEASUREMENTS_H
#define ARGENTUM_WINDOW_MEASUREMENTS_H
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
    game_area_t list;
    game_area_t equipped;
    game_area_t life;
    game_area_t mana;
    game_area_t experience;
    WindowMeasurements();
    ~WindowMeasurements();
    void initialize(int numberOfTilesInWidth, int numberOfTilesInHeight,
                    int screenWidth, int screenHeight);
};


#endif //ARGENTUM_WINDOW_MEASUREMENTS_H
