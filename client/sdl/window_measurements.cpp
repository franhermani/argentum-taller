//
// Created by martinrosas on 5/7/20.
//

#include "window_measurements.h"
WindowMeasurements::WindowMeasurements(int numberOfTilesInWidth, int numberOfTilesInHeight,
                                       int screenWidth, int screenHeight) :
                                       numberOfTilesInWidth(numberOfTilesInWidth),
                                       numberOfTilesInHeight(numberOfTilesInHeight){
    frame.x_pixel_begin = screenWidth / 50;
    frame.x_pixel_end = (screenWidth / 4) * 3;
    frame.y_pixel_begin = screenHeight / 5;
    frame.y_pixel_end = (screenHeight / 100) * 99;
    xWidthTileSize = (frame.x_pixel_end - frame.x_pixel_begin) /
            numberOfTilesInWidth;
    yHeightTileSize = (frame.y_pixel_end - frame.y_pixel_begin) /
            numberOfTilesInHeight;
    inventory.x_pixel_begin =  (screenWidth / 100) * 84;
    inventory.x_pixel_end =  (screenWidth / 100) * 102;
    inventory.y_pixel_begin = screenHeight / 4;
    inventory.y_pixel_end = (screenHeight /100) * 64;
    equipped.x_pixel_begin =  (screenWidth / 100) * 1;
    equipped.x_pixel_end =  (screenWidth / 100) * 45;
    equipped.y_pixel_begin = (screenHeight / 100) * 4;
    equipped.y_pixel_end = (screenHeight /100) * 15;
    life.x_pixel_begin = (int)  (((float) screenWidth/100) * 78.8);
    life.x_pixel_end =  (int) (((float) screenWidth/100) * 86.5);
    life.y_pixel_begin = (int) (((float) screenHeight/100) * 87);
    life.y_pixel_end = (int) (((float) screenHeight/100) * 88.5);
    mana.x_pixel_begin = (int)  (((float) screenWidth/100) * 78.8);
    mana.x_pixel_end =  (int) (((float) screenWidth/100) * 86.5);
    mana.y_pixel_begin = (int) (((float) screenHeight/100) * 84.1);
    mana.y_pixel_end = (int) (((float) screenHeight/100) * 85.6);
    experience.x_pixel_begin = (int)  (((float) screenWidth/100) * 78.8);
    experience.x_pixel_end =  (int) (((float) screenWidth/100) * 86.5);
    experience.y_pixel_begin = (int) (((float) screenHeight/100) * 89.9);
    experience.y_pixel_end = (int) (((float) screenHeight/100) * 91.4);
}
WindowMeasurements::~WindowMeasurements() {}