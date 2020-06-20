#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <string>
#include <vector>
#include <SDL2/SDL_image.h>
#include "../sdl/window.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npcs.h"

struct npc_pos {
    int x;
    int y;
    Npc npc_name;
};

class GameRender {
    const int screenWidth;
    const int screenHeight;
    int blocksWidth;
    int blocksHeight;
    SDLWindow window;
    // TODO arreglar private y public
    std::map<Terrain, Surface *> terrainSurfacesMap;
    std::map<Npc, Surface *> npcSurfacesMap;
    std::map<Terrain, std::string> terrainSurfacesPaths;
    std::map<Npc, std::string> npcSurfacesPaths;

private:
    // inicializa en terrainSurfacesMap las surfaces necesarias faltantes
    void createNecessaryTerrains(std::vector<std::vector<Terrain>> &matrix);

    // inicializa en npcSurfacesMap las surfaces necesarias faltantes
    void createNecessaryNpcs(std::vector<npc_pos> &npc_positions);

public:
    //Constructor
    GameRender(const int screenWidth, const int screenHeight);

    //Destructor
    ~GameRender();

    //Renderizador de pisos
    void renderTerrain(std::vector<std::vector<Terrain>> &matrix);

    //Renderizador de npcs
    void renderNpcs(std::vector<npc_pos> &npc_positions);

    //Inicializa paths a archivos de imagenes para surfaces
    void loadSurfacePaths();

    //Inicializador de SDL
    int init();

    //Renderizador de jugada completa
    void render(std::vector<Terrain> &received_terrain,
                std::vector<npc_pos> &npc_positions);

    void setTilesSize(int width, int height);
};

#endif //ARGENTUM_GAME_RENDER_H
