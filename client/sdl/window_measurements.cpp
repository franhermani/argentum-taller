
#include <iostream>
#include "window_measurements.h"

WindowMeasurements::WindowMeasurements() {}


void WindowMeasurements::initialize(int receivedNumberOfTilesInWidth,
        int receivedNumberOfTilesInHeight, int receivedScreenWidth,
        int receivedScreenHeight) {
    numberOfTilesInWidth = receivedNumberOfTilesInWidth;
    numberOfTilesInHeight = receivedNumberOfTilesInHeight;
    screenWidth = receivedScreenWidth;
    screenHeight = receivedScreenHeight;
    frame = {screenWidth / 50, (screenWidth / 4) * 3,
             screenHeight / 5, (screenHeight / 100) * 99};

    xWidthTileSize = (frame.x_pixel_end - frame.x_pixel_begin) /
            numberOfTilesInWidth;
    yHeightTileSize = (frame.y_pixel_end - frame.y_pixel_begin) /
            numberOfTilesInHeight;
    //TODO el 100 es el granular fijarse bien sacarlo afuera
    xWidthGranularTileSize =  ((frame.x_pixel_end - frame.x_pixel_begin) /
            (numberOfTilesInWidth*100.0));
    yHeightGranularTileSize = ((frame.y_pixel_end - frame.y_pixel_begin) /
            (numberOfTilesInHeight*100.0));
    //std::cout << "\n\n aa "<< frame.y_pixel_end - frame.y_pixel_begin;
    //std::cout << "\n\nx width tile size "<< xWidthTileSize << "\n";
    //std::cout << "\n\n x with granular tile size " << xWidthGranularTileSize << "\n";

    initializeItemInfo(screenWidth, screenHeight);
    initializePlayerInfo(screenWidth, screenHeight);
    initializeStaticAreas();
}

void WindowMeasurements::updateResolution(int width, int height) {
    initialize(numberOfTilesInWidth, numberOfTilesInHeight, width, height);
}

void WindowMeasurements::initializeStaticAreas() {
    //TODO ver si frame sigue teniendo sentido que exista
    worldStaticRect.x = frame.x_pixel_begin;
    worldStaticRect.y = frame.y_pixel_begin;
    worldStaticRect.w = frame.x_pixel_end - frame.x_pixel_begin;
    worldStaticRect.h = frame.y_pixel_end - frame.y_pixel_begin;

    gameFrameStaticRect.x = 0;
    gameFrameStaticRect.y = 0;
    gameFrameStaticRect.w = screenWidth;
    gameFrameStaticRect.h = screenHeight;

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
    listGoldQuantityStaticRect.x = listGoldStaticRect.x;
    listGoldQuantityStaticRect.y = listGoldStaticRect.y +
            (int) (listGoldStaticRect.h *1.1);
    listGoldQuantityStaticRect.w = (list_gold_area.x_pixel_end -
                            list_gold_area.x_pixel_begin);
    listGoldQuantityStaticRect.h = (list_gold_area.y_pixel_end -
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

    list_prices = {(int) (screenWidth / 100.0) * 44,
            (int) (screenWidth / 100.0) * 74,
            (int) (screenHeight / 100.0) * 10,
            (int) (screenHeight /100.0) * 15};

    listGold = {(int) (screenWidth / 100.0) * 75,
                 (int) (screenWidth / 100.0) * 80,
                 (int) (screenHeight / 100.0) * 3,
                 (int) (screenHeight /100.0) * 10};

    equipped = {(screenWidth / 100) * 1, (screenWidth / 100) * 45,
                (screenHeight / 100) * 4, (screenHeight /100) * 15};
}

WindowMeasurements::~WindowMeasurements() {}
