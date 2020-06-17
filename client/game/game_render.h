#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <string>
#include <vector>
#include <SDL2/SDL_image.h>
#include "../sdl/window.h"
#include "../../common/defines/terrain.h"
#include "../../common/defines/npc.h"

struct npc_pos {
    int x;
    int y;
    Npc npc_name;
};

class GameRender {
    const int screenWidth;
    const int screenHeight;
    const int blocksWidth;
    const int blocksHeight;
    SDLWindow window;
    //TODO
    std::map<Terrain, Surface*> terrainSurfacesMap;
    std::map<Npc, Surface*> npcSurfacesMap;
    std::map<Terrain, std::string> terrainSurfacesPaths;

public:
    //Constructor
    GameRender(const int screenWidth, const int screenHeight,
               const int blocksWidth, const int blocksHeight);

    //Destructor
    ~GameRender();

    //Renderizador de pisos
    void renderTerrain(std::vector<std::vector<Terrain>>& matrix);

    //Renderizador de npcs
    void renderNpcs(std::vector<npc_pos>& npc_positions);

    //Inicializador de SDL
    int init();

    //Renderizador de jugada completa
    void render(std::vector<Terrain>& received_terrain,
            std::vector<npc_pos>& npc_positions);
};

#endif //ARGENTUM_GAME_RENDER_H
