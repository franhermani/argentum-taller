//
// Created by martinrosas on 4/7/20.
//

#ifndef ARGENTUM_PLAYER_INFO_BARS_H
#define ARGENTUM_PLAYER_INFO_BARS_H

#endif //ARGENTUM_PLAYER_INFO_BARS_H



enum playerInfoBars {
    LIFE,
    MANA,
    EXPERIENCE,
    BACKGROUND
};

typedef struct {
    int x_pixel_begin;
    int x_pixel_end;
    int y_pixel_begin;
    int y_pixel_end;
} game_area_t;