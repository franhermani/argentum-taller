
#ifndef ARGENTUM_GAME_IMAGES_MANAGER_H
#define ARGENTUM_GAME_IMAGES_MANAGER_H
#include <vector>
#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "../../common/defines/commands.h"
#include "../../common/thread.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/states.h"
#include "../../common/defines/world_structs.h"
#include "../sdl/surface.h"
#include "../sdl/window.h"
#include "image_path_container.h"

class GameImagesManager {
    ImagePathContainer pathContainer;
    std::map<int, std::map<int, Surface *>> creatureSurfacesMap;
    std::map<int, std::map<int, Surface *>> npcSurfacesMap;
    std::map<int, std::map<int, Surface *>> playerSurfacesMap;
    std::map<stateType, std::map<int, Surface *>> stateSurfacesMap;
    std::map<int, std::map<int, Surface *>> attackSurfacesMap;
    std::map<int, std::map<int, Surface *>> equippedWeaponSurfacesMap;
    std::map<int, Surface *> itemSurfacesMap;
    std::map<int, Surface *> infoSurfacesMap;
    std::map<int, Surface*> animatedStateMap;
    std::map<std::string, Surface*> textSurfaces;
    Surface* goldSurface;
    Surface* gameFrameSurface;
    Surface* worldSurface;
    TTF_Font* mainFont;
    SDL_Color mainColor;
    SDLWindow& window;

    friend class GameRender;


    //Inicializa paths a archivos de imagenes para surfaces
    void loadSurfacePaths();
    void initCreatures();
    void initNpc();
    void initPlayers();
    void initAttack();
    void initEquipped();
    void initFrame();

    // inicializadores lazy de surfaces
    void createNecessaryFrameItems(std::vector<uint8_t>& items);
    Surface* getEquipped(int weapon, int orientation);


public:
    //Constructor
    explicit GameImagesManager(SDLWindow& window);

    //Destructor
    ~GameImagesManager();
    // Constructor y asignacion por copia deshabilitados
    GameImagesManager(const GameImagesManager& other) = delete;
    GameImagesManager& operator=(const GameImagesManager& other) = delete;
    Surface* operator()(player_t& player);
    Surface* operator()(int item_type);
    Surface* operator()(stateType state, int orientation);
    Surface* operator()(attack_t& attack);
    Surface* operator()(creature_t& creature);
    Surface* operator()(npc_t& npc);
    Surface* operator()(std::string str);
    std::vector<Surface*> operator()(std::vector<list_item_t> items);

    Surface* animation(stateType state);
};


#endif //ARGENTUM_GAME_IMAGES_MANAGER_H
