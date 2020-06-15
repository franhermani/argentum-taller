
#ifndef ARGENTUM_GAME_RENDER_H
#define ARGENTUM_GAME_RENDER_H
#include <string>
#include <vector>
#include "connection_handler.h"
#include "../sdl/window.h"
#include <SDL2/SDL_image.h>


class GameRender {
private:
    const int screen_width;
    const int screen_height;
    const int blocks_width;
    const int blocks_height;
    SDLWindow window;
public:
    GameRender(const int screen_width, const int screen_height, const int blocks_width, const int blocks_height);
    ~GameRender();
    int init();
    void play();
};


#endif //ARGENTUM_GAME_RENDER_H
