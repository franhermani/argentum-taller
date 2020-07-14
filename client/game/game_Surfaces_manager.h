
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
    std::map<int, std::map<int, Surface *>> creatureSurfacesMap;
    std::map<int, std::map<int, Surface *>> npcSurfacesMap;
    std::map<int, std::map<int, Surface *>> playerSurfacesMap;
    std::map<int, Surface *> ghostSurfacesMap;
    std::map<int, std::map<int, Surface *>> attackSurfacesMap;
    std::map<int, std::map<int, Surface *>> equippedWeaponSurfacesMap;
    std::map<int, Surface *> itemSurfacesMap;
    std::map<int, Surface *> infoSurfacesMap;
    Surface* goldSurface;
    Surface* gameFrameSurface;
    Surface* worldSurface;
    std::map<int, std::map<int, std::string>> npcSurfacesPaths;
    std::map<int, std::map<int, std::string>> equippedWeaponSurfacesPaths;
    std::map<int, std::map<int, std::string>> creatureSurfacesPaths;
    std::map<int, std::map<int, std::string>> playerSurfacesPaths;
    std::map<int, std::map<int, std::string>> attackSurfacesPaths;
    std::map<int, std::string> itemSurfacesPaths;
    std::vector<std::vector<Terrain>> floor;
    SDLWindow& window;

    Surface* getTextSurface(std::string text);

    friend class GameRender;


    //Inicializa paths a archivos de imagenes para surfaces
    void loadSurfacePaths();
    void loadCreaturePaths();
    void loadNpcPaths();
    void loadPlayerPaths();
    void loadItemPaths();
    void loadAttackPaths();
    void loadEquippedPaths();


    void createFrameSurfaces();

    // inicializadores lazy de surfaces
    void createNecessaryPlayers(std::vector<player_t>& players);
    void createNecessaryNpcs(std::vector<npc_t>& npcs);
    void createNecessaryCreatures(std::vector<creature_t>& creatures);
    void createNecessaryItems(std::vector<item_t>& items);
    void createNecessaryListItems(std::vector<list_item_t> items);
    void createNecessaryFrameItems(std::vector<uint8_t>& items);
    void createNecessaryEquipped(std::vector<player_t>& players);
    void createNecessaryAttacks(std::vector<attack_t>& attacks);


public:
    //Constructor
    explicit GameSurfacesManager(SDLWindow& window);

    //Destructor
    ~GameSurfacesManager();

    // Constructor y asignacion por copia deshabilitados
    GameSurfacesManager(const GameSurfacesManager& other) = delete;
    GameSurfacesManager& operator=(const GameSurfacesManager& other) = delete;
};


#endif //ARGENTUM_GAME_SURFACES_MANAGER_H
