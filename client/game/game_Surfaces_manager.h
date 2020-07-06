
#ifndef ARGENTUM_GAME_SURFACES_MANAGER_H
#define ARGENTUM_GAME_SURFACES_MANAGER_H
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
    Surface* goldSurface;
    std::map<Terrain, std::string> terrainSurfacesPaths;
    std::map<int, std::map<int, std::string>> npcSurfacesPaths;
    std::map<int, std::map<int, std::string>> creatureSurfacesPaths;
    std::map<int, std::map<int, std::string>> playerSurfacesPaths;
    std::map<int, std::string> floorItemSurfacesPaths;
    std::vector<std::vector<Terrain>> floor;
    SDLWindow& window;

    friend class GameRender;

    //creador de surface de marco. Se utiliza siempre
    Surface* createGameFrameSurface();

    //Inicializa paths a archivos de imagenes para surfaces
    void loadSurfacePaths();
    void loadCreaturePaths();
    void loadNpcPaths();
    void loadPlayerPaths();
    void loadItemPaths();

    // inicializadores lazy de surfaces
    void createNecessaryTerrains(std::vector<std::vector<Terrain>>& matrix);
    void createNecessaryPlayers(std::vector<player_t>& players);
    void createNecessaryNpcs(std::vector<npc_t>& npcs);
    void createNecessaryCreatures(std::vector<creature_t>& creatures);
    void createNecessaryItems(std::vector<item_t>& items);
    void createNecessaryFrameItems(std::vector<uint8_t>& items);

public:
    //Constructor
    GameSurfacesManager(SDLWindow& window);

    //Destructor
    ~GameSurfacesManager();

    // Constructor y asignacion por copia deshabilitados
    GameSurfacesManager(const GameSurfacesManager& other) = delete;
    GameSurfacesManager& operator=(const GameSurfacesManager& other) = delete;
};


#endif //ARGENTUM_GAME_SURFACES_MANAGER_H
