
#ifndef ARGENTUM_GAME_RENDER_H
#define ARGENTUM_GAME_RENDER_H
#include <string>
#include <vector>
#include "connection_handler.h"
#include "../sdl/window.h"
#include <SDL2/SDL_image.h>


class GameRender {
private:
    const int screenWidth;
    const int screenHeight;
    const int blocksWidth;
    const int blocksHeight;
    SDLWindow window;
    //std::map<terrain, Surface> terrain_surfaces_map;
    //std::map<npc, Surface> npc_surfaces_map;
public:
    GameRender(const int screenWidth, const int screenHeight, const int blocksWidth, const int blocksHeight);
    ~GameRender();
    int init();
    void play();
};


#endif //ARGENTUM_GAME_RENDER_H
