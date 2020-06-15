
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
    //TODO
    //std::map<terrain, Surface> terrainSurfacesMap;
    //std::map<npc, Surface> npcSurfacesMap;
public:
    //Constructor
    GameRender(const int screenWidth, const int screenHeight, const int blocksWidth, const int blocksHeight);

    //Destructor
    ~GameRender();

    //Renderizador de pisos
    void render_terrain(std::vector<std::vector<terrain>>& matrix);

    //Renderizador de npcs
    void render_npcs(std::vector<npc_pos>& npc_positions);

    //Inicializador de SDL
    int init();

    //Renderizador de jugada completa
    void play(std::vector<terrain>& received_terrain, std::vector<npc_pos>& npc_positions);
};


#endif //ARGENTUM_GAME_RENDER_H
