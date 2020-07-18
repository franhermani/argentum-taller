
#ifndef ARGENTUM_GAME_SURFACES_MANAGER_H
#define ARGENTUM_GAME_SURFACES_MANAGER_H
#include <vector>
#include <map>
#include <string>
#include "../../common/defines/commands.h"
#include "../../common/thread.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/states.h"
#include "../../common/defines/world_structs.h"
#include "../sdl/surface.h"
#include "../sdl/window.h"

class GameSurfacesManager {
    std::map<int, std::map<int, Surface *>> creatureSurfacesMap;
    std::map<int, std::map<int, Surface *>> npcSurfacesMap;
    std::map<int, std::map<int, Surface *>> playerSurfacesMap;
    std::map<stateType, std::map<int, Surface *>> stateSurfacesMap;
    std::map<int, std::map<int, Surface *>> attackSurfacesMap;
    std::map<int, std::map<int, Surface *>> equippedWeaponSurfacesMap;
    std::map<int, Surface *> itemSurfacesMap;
    std::map<int, Surface *> infoSurfacesMap;
    std::vector<Surface*> textSurfaces;
    Surface* goldSurface;
    Surface* gameFrameSurface;
    Surface* worldSurface;
    std::map<int, std::map<int, std::string>> npcSurfacesPaths;
    std::map<int, std::map<int, std::string>> equippedWeaponSurfacesPaths;
    std::map<int, std::map<int, std::string>> creatureSurfacesPaths;
    std::map<int, std::map<int, std::string>> playerSurfacesPaths;
    std::map<int, std::map<int, std::string>> attackSurfacesPaths;
    std::map<int, std::string> itemSurfacesPaths;
    SDLWindow& window;

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
    void createNecessaryFrameItems(std::vector<uint8_t>& items);
    Surface* getEquipped(int weapon, int orientation);


public:
    //Constructor
    explicit GameSurfacesManager(SDLWindow& window);

    //Destructor
    ~GameSurfacesManager();
    // Constructor y asignacion por copia deshabilitados
    GameSurfacesManager(const GameSurfacesManager& other) = delete;
    GameSurfacesManager& operator=(const GameSurfacesManager& other) = delete;
    Surface* operator()(player_t& player);
    Surface* operator()(int item_type);
    Surface* operator()(stateType state, int orientation);
    Surface* operator()(attack_t& attack);
    Surface* operator()(creature_t& creature);
    Surface* operator()(npc_t& npc);
    Surface* operator()(std::string str);
    std::vector<Surface*> operator()(std::vector<list_item_t> items);

};


#endif //ARGENTUM_GAME_SURFACES_MANAGER_H
