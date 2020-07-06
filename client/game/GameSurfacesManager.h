
#ifndef ARGENTUM_GAMESURFACESMANAGER_H
#define ARGENTUM_GAMESURFACESMANAGER_H
#include <vector>
#include <map>
#include <string>
#include "../../common/defines/commands.h"
#include "../../common/thread.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/world_structs.h"
#include "../sdl/surface.h"
#include "../sdl/window.h"

class GameSurfacesManager {
    std::map<Terrain, Surface *> terrainSurfacesMap;
    std::map<int, std::map<int, Surface *>> creatureSurfacesMap;
    std::map<int, std::map<int, Surface *>> npcSurfacesMap;
    std::map<int, std::map<int, Surface *>> playerSurfacesMap;
    std::map<int, Surface *> floorItemSurfacesMap;
    std::map<int, Surface *> infoSurfacesMap;
    std::map<Terrain, std::string> terrainSurfacesPaths;
    std::map<int, std::map<int, std::string>> npcSurfacesPaths;
    std::map<int, std::map<int, std::string>> creatureSurfacesPaths;
    std::map<int, std::map<int, std::string>> playerSurfacesPaths;
    std::map<int, std::string> floorItemSurfacesPaths;
    std::vector<std::vector<Terrain>> floor;
    SDLWindow& window;


    GameSurfacesManager(SDLWindow& window);
    ~GameSurfacesManager();
    // inicializa en terrainSurfacesMap las surfaces necesarias faltantes
    void createNecessaryTerrains(std::vector<std::vector<Terrain>>& matrix);

    // inicializa en playerSurfacesMap las surfaces necesarias faltantes
    void createNecessaryPlayers(std::vector<player_t>& players);

    // inicializa en npcSurfacesMap las surfaces necesarias faltantes
    void createNecessaryNpcs(std::vector<npc_t>& npcs);

    void createNecessaryCreatures(std::vector<creature_t>& creatures);

    void createNecessaryFloorItems(std::vector<item_t>& items);

    Surface* createGameFrameSurface();

    //Inicializa paths a archivos de imagenes para surfaces
    void loadSurfacePaths();
    friend class GameRender;

};


#endif //ARGENTUM_GAMESURFACESMANAGER_H
