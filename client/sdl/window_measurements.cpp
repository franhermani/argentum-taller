
#include "window_measurements.h"

WindowMeasurements::WindowMeasurements() {}


void WindowMeasurements::initialize(int numberOfTilesInWidth,
        int numberOfTilesInHeight, int screenWidth, int screenHeight) {
    numberOfTilesInWidth = numberOfTilesInWidth;
    numberOfTilesInHeight = numberOfTilesInHeight;
    screenWidth = screenWidth;
    screenHeight = screenHeight;
    frame = {screenWidth / 50, (screenWidth / 4) * 3,
             screenHeight / 5, (screenHeight / 100) * 99};

    xWidthTileSize = (frame.x_pixel_end - frame.x_pixel_begin) /
            numberOfTilesInWidth;
    yHeightTileSize = (frame.y_pixel_end - frame.y_pixel_begin) /
            numberOfTilesInHeight;

    initializePlayerInfo(screenWidth, screenHeight);
    initializeItemInfo(screenWidth, screenHeight);
}

void WindowMeasurements::initializePlayerInfo(int screenWidth,
        int screenHeight) {
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

void WindowMeasurements::initializeItemInfo(int screenWidth,
        int screenHeight) {
    inventory = {(screenWidth / 100) * 84, (screenWidth / 100) * 102,
                 screenHeight / 4, (screenHeight /100) * 64};

    inventory_gold = {(int) (screenWidth / 100.0) * 85,
                      (int) (screenWidth / 100.0) * 89,
                      (int) (screenHeight / 100.0 * 95),
                      int (screenHeight /100.0 * 99)};

    list = {(int) (screenWidth / 100.0) * 44,
            (int) (screenWidth / 100.0) * 74,
            (int) (screenHeight / 100.0) * 5,
            (int) (screenHeight /100.0) * 15};

    list_gold = {(int) (screenWidth / 100.0) * 75,
                 (int) (screenWidth / 100.0) * 80,
                 (int) (screenHeight / 100.0) * 3,
                 (int) (screenHeight /100.0) * 10};

    equipped = {(screenWidth / 100) * 1, (screenWidth / 100) * 45,
                (screenHeight / 100) * 4, (screenHeight /100) * 15};

}

WindowMeasurements::~WindowMeasurements() {}
