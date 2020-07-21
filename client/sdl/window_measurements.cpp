
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
    initializeItemInfo(screenWidth, screenHeight);
    initializePlayerInfo(screenWidth, screenHeight);
    initializeMainStaticAreas();
    initializeInfoStaticAreas();
    initializeGoldStaticAreas();
}

void WindowMeasurements::updateResolution(int width, int height) {
    initialize(numberOfTilesInWidth, numberOfTilesInHeight, width, height);
}

SDL_Rect WindowMeasurements::measureAnimatedRect(int iteration) {
    SDL_Rect origin_rect = animatedObjStaticRect;
    origin_rect.x = origin_rect.x*iteration;
    origin_rect.y = origin_rect.y*iteration;
    return origin_rect;
}

WindowMeasurements::~WindowMeasurements() {}

void WindowMeasurements::initializeGoldStaticAreas() {
    game_area_t& inventory_gold_area = inventoryGold;
    inventoryGoldStaticRect.x = inventory_gold_area.x_pixel_begin;
    inventoryGoldStaticRect.y = inventory_gold_area.y_pixel_begin;
    inventoryGoldStaticRect.w = (inventory_gold_area.x_pixel_end -
                                 inventory_gold_area.x_pixel_begin);
    inventoryGoldStaticRect.h = (inventory_gold_area.y_pixel_end -
                                 inventory_gold_area.y_pixel_begin);


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

void WindowMeasurements::initializeInfoStaticAreas() {
    game_area_t& level_area = level;
    levelStaticRect.x = level_area.x_pixel_begin;
    levelStaticRect.y = level_area.y_pixel_begin;
    levelStaticRect.w = (level_area.x_pixel_end -
                         level_area.x_pixel_begin);
    levelStaticRect.h = (level_area.y_pixel_end -
                         level_area.y_pixel_begin);

    game_area_t& name_area = name;
    nameStaticRect.x = name_area.x_pixel_begin;
    nameStaticRect.y = name_area.y_pixel_begin;
    nameStaticRect.w = (name_area.x_pixel_end -
                        name_area.x_pixel_begin);
    nameStaticRect.h = (name_area.y_pixel_end -
                        name_area.y_pixel_begin);
}


void WindowMeasurements::initializeMainStaticAreas() {
    worldStaticRect.x = frame.x_pixel_begin;
    worldStaticRect.y = frame.y_pixel_begin;
    worldStaticRect.w = frame.x_pixel_end - frame.x_pixel_begin;
    worldStaticRect.h = frame.y_pixel_end - frame.y_pixel_begin;

    gameFrameStaticRect.x = 0;
    gameFrameStaticRect.y = 0;
    gameFrameStaticRect.w = screenWidth;
    gameFrameStaticRect.h = screenHeight;


    animatedObjStaticRect.x = 80;
    animatedObjStaticRect.y = 175;
    animatedObjStaticRect.w = 80;
    animatedObjStaticRect.h = 175;
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

    name =  {(int)  ((screenWidth/100.0) *  84.3),
             (int) ((screenWidth/100.0) * 93.0),
             (int) ((screenHeight/100.0) * 92.7),
             (int) ((screenHeight/100.0) * 97.2)};
}

void WindowMeasurements::initializeItemInfo(int screenWidth,
        int screenHeight) {
    inventory = {(screenWidth / 100) * 84, (screenWidth / 100) * 102,
                 screenHeight / 4, (screenHeight /100) * 64};

    inventoryGold = {(int) ((screenWidth / 100.0) * 93),
                (int) ((screenWidth / 100.0) * 98.0),
                (int) ((screenHeight / 100.0) * 74.2),
                (int) ((screenHeight /100.0) * 78)};

    list = {(int) (screenWidth / 100.0) * 46,
            (int) (screenWidth / 100.0) * 74,
            (int) (screenHeight / 100.0) * 5,
            (int) (screenHeight /100.0) * 15};

    list_prices = {(int) (screenWidth / 100.0) * 46,
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
