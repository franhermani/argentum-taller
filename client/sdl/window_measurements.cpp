
#include <iostream>
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

    initializeItemInfo(screenWidth, screenHeight);
    initializePlayerInfo(screenWidth, screenHeight);
    initializeStaticAreas();
}

void WindowMeasurements::initializeStaticAreas() {
    gameFrameStaticRect.x = 0;
    gameFrameStaticRect.y = 0;
    gameFrameStaticRect.w = screenWidth;
    gameFrameStaticRect.h = screenHeight;

    std::cout << "ahora inicializo static area de oro\n";

    game_area_t& inventory_gold_area = inventoryGold;
    inventoryGoldStaticRect.x = inventory_gold_area.x_pixel_begin;
    inventoryGoldStaticRect.y = inventory_gold_area.y_pixel_begin;
    inventoryGoldStaticRect.w = (inventory_gold_area.x_pixel_end -
                                 inventory_gold_area.x_pixel_begin);
    inventoryGoldStaticRect.h = (inventory_gold_area.y_pixel_end -
                                 inventory_gold_area.y_pixel_begin);

    game_area_t& level_area = level;
    levelStaticRect.x = level_area.x_pixel_begin;
    levelStaticRect.y = level_area.y_pixel_begin;
    levelStaticRect.w = (level_area.x_pixel_end -
            level_area.x_pixel_begin);
    levelStaticRect.h = (level_area.y_pixel_end -
            level_area.y_pixel_begin);


    game_area_t& list_gold_area = listGold;
    listGoldStaticRect.x = list_gold_area.x_pixel_begin;
    listGoldStaticRect.y = list_gold_area.y_pixel_begin;
    listGoldStaticRect.w = (list_gold_area.x_pixel_end -
                            list_gold_area.x_pixel_begin);
    listGoldStaticRect.h = (list_gold_area.y_pixel_end -
                            list_gold_area.y_pixel_begin);
}


void WindowMeasurements::initializePlayerInfo(int screenWidth,
        int screenHeight) {
    life = {(int) ((screenWidth/100.0) * 78.8),
            (int) ((screenWidth/100.0) * 86.5),
            (int) ((screenHeight/100.0) * 81.1),
            (int) ((screenHeight/100.0) * 82.6)};

    mana = {(int) ((screenWidth/100.0) * 78.8),
            (int) ((screenWidth/100.0) * 86.5),
            (int) ((screenHeight/100.0) * 84.8),
            (int) ((screenHeight/100.0) * 86.3)};

    experience = {(int)  ((screenWidth/100.0) *  78.8),
                  (int) ((screenWidth/100.0) * 86.5),
                  (int) ((screenHeight/100.0) * 88.7),
                  (int) ((screenHeight/100.0) * 90.2)};


    level = {(int) ((screenWidth / 100.0) * 91.1),
             (int) ((screenWidth / 100.0) * 93.8),
             (int) ((screenHeight / 100.0) * 84.8),
             (int) ((screenHeight /100.0) * 90)};
}

void WindowMeasurements::initializeItemInfo(int screenWidth,
        int screenHeight) {
    inventory = {(screenWidth / 100) * 84, (screenWidth / 100) * 102,
                 screenHeight / 4, (screenHeight /100) * 64};

    /*TODO ESTO AHORA VA A SER LA POSICION DE LAS EXCEPCIONES
    exceptions = {(int) (screenWidth / 100.0) * 85,
                      (int) (screenWidth / 100.0) * 89,
                     (int) ((screenHeight / 100.0) * 95),
                     (int) ((screenHeight /100.0) * 99)};
*/

    inventoryGold = {(int) ((screenWidth / 100.0) * 93),
                (int) ((screenWidth / 100.0) * 98.0),
                (int) ((screenHeight / 100.0) * 74.2),
                (int) ((screenHeight /100.0) * 78)};


    list = {(int) (screenWidth / 100.0) * 44,
            (int) (screenWidth / 100.0) * 74,
            (int) (screenHeight / 100.0) * 5,
            (int) (screenHeight /100.0) * 15};

    listGold = {(int) (screenWidth / 100.0) * 75,
                 (int) (screenWidth / 100.0) * 80,
                 (int) (screenHeight / 100.0) * 3,
                 (int) (screenHeight /100.0) * 10};

    equipped = {(screenWidth / 100) * 1, (screenWidth / 100) * 45,
                (screenHeight / 100) * 4, (screenHeight /100) * 15};
}

WindowMeasurements::~WindowMeasurements() {}
