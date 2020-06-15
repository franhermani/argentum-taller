
#ifndef ARGENTUM_GAME_RENDER_H
#define ARGENTUM_GAME_RENDER_H
#include <string>
#include <vector>
#include "connection_handler.h"
#include "../sdl/window.h"
#include <SDL2/SDL_image.h>

struct npc_pos {
    int x;
    int y;
    npc npc_name;
};

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
    void render_terrain(std::vector<std::vector<terrain>>& matrix);
    void render_npcs(std::vector<npc_pos>& npc_positions);
    int init();
    void play();
};


#endif //ARGENTUM_GAME_RENDER_H
