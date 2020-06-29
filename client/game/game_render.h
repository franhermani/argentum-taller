#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL_image.h>
#include "../sdl/window.h"
#include "../../common/thread.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/world_structs.h"
#include "map_monitor.h"


class GameRender : public Thread {
    const int screenWidth;
    const int screenHeight;
    MapMonitor& mapMonitor;
    int blocksWidth;
    int blocksHeight;
    SDLWindow window;
    // TODO arreglar private y public
    std::map<Terrain, Surface *> terrainSurfacesMap;
    // TODO: borrar esto, Npc ya no existe
//    std::map<Npc, Surface *> npcSurfacesMap;
    std::map<int, std::map<int, Surface *>> playerSurfacesMap;
    std::map<Terrain, std::string> terrainSurfacesPaths;
    // TODO: borrar esto, Npc ya no existe
//    std::map<Npc, std::string> npcSurfacesPaths;
    std::map<int, std::map<int, std::string>> playerSurfacesPaths;
    std::vector<std::vector<Terrain>> floor;


private:
    // inicializa en terrainSurfacesMap las surfaces necesarias faltantes
    void createNecessaryTerrains(std::vector<std::vector<Terrain>>& matrix);

    // inicializa en playerSurfacesMap las surfaces necesarias faltantes
    void createNecessaryPlayers(std::vector<player_t>& players);


public:
    //Constructor
    GameRender(const int screenWidth, const int screenHeight,
               MapMonitor &mapMonitor);

    //Destructor
    ~GameRender();


    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;

    //Renderizador de pisos
    void renderTerrain(std::vector<std::vector<Terrain>> matrix);

    //Renderizador de players
    void renderPlayers(std::vector<player_t> &players);

    //Inicializa paths a archivos de imagenes para surfaces
    void loadSurfacePaths();

    //Inicializador de SDL
    int init();

    void setTilesSize(int width, int height);

    Surface* createGameFrameSurface();
};

#endif //ARGENTUM_GAME_RENDER_H
