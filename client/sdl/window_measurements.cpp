
#include "window_measurements.h"

WindowMeasurements::WindowMeasurements() {}
void WindowMeasurements::initialize(int numberOfTilesInWidth,
        int numberOfTilesInHeight, int screenWidth, int screenHeight) {
    //todo separar en varias funciones
    numberOfTilesInWidth = numberOfTilesInWidth;
    numberOfTilesInHeight = numberOfTilesInHeight;

    frame = {screenWidth / 50, (screenWidth / 4) * 3,
             screenHeight / 5, (screenHeight / 100) * 99};

    xWidthTileSize = (frame.x_pixel_end - frame.x_pixel_begin) /
            numberOfTilesInWidth;
    yHeightTileSize = (frame.y_pixel_end - frame.y_pixel_begin) /
            numberOfTilesInHeight;

    inventory = {(screenWidth / 100) * 84, (screenWidth / 100) * 102,
                 screenHeight / 4, (screenHeight /100) * 64};

    list = {(int) (screenWidth / 100.0) * 44, (int) (screenWidth / 100.0) * 74,
            (int) (screenHeight / 100.0) * 5, (int) (screenHeight /100.0) * 15};

    equipped = {(screenWidth / 100) * 1, (screenWidth / 100) * 45,
                (screenHeight / 100) * 4, (screenHeight /100) * 15};

    life = {(int) ((screenWidth/100.0) * 78.8),
            (int) ((screenWidth/100.0) * 86.5),
            (int) ((screenHeight/100.0) * 87),
            (int) ((screenHeight/100.0) * 88.5)};

    mana = {(int) ((screenWidth/100.0) * 78.8),
            (int) ((screenWidth/100.0) * 86.5),
            (int) ((screenHeight/100.0) * 84.1),
            (int) ((screenHeight/100.0) * 85.6)};

    experience = {(int)  ((screenWidth/100.0) * 78.8),
                  (int) ((screenWidth/100.0) * 86.5),
                  (int) ((screenHeight/100.0) * 89.9),
                  (int) ((screenHeight/100.0) * 91.4)};
}
WindowMeasurements::~WindowMeasurements() {}
