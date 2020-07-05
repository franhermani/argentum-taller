//
// Created by martinrosas on 5/7/20.
//

#ifndef ARGENTUM_WINDOW_MEASUREMENTS_H
#define ARGENTUM_WINDOW_MEASUREMENTS_H
#include "render_structs.h"


class WindowMeasurements {
    int numberOfTilesInWidth;
    int numberOfTilesInHeight;
    int xWidthTileSize;
    int yHeightTileSize;
    int screenHeight;
    int screenWidth;
    game_area_t frame;
    game_area_t inventory;
    game_area_t equipped;
    game_area_t life;
    game_area_t mana;
    game_area_t experience;

    WindowMeasurements(int numberOfTilesInWidth, int numberOfTilesInHeight,
                       int screenWidth, int screenHeight);
    ~WindowMeasurements();
};


#endif //ARGENTUM_WINDOW_MEASUREMENTS_H
