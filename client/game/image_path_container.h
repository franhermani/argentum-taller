
#ifndef ARGENTUM_IMAGE_PATH_CONTAINER_H
#define ARGENTUM_IMAGE_PATH_CONTAINER_H
#include <vector>
#include <map>
#include <string>
#include "../../common/defines/commands.h"
#include "../../common/thread.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/states.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/items.h"
#include "../../common/defines/attacks.h"

struct ImagePathContainer {
    ImagePathContainer();
    std::map<int, std::string> animatedStatePaths;
    std::map<int, std::map<int, std::string>> npcSurfacesPaths;
    std::map<int, std::map<int, std::string>> equippedWeaponSurfacesPaths;
    std::map<int, std::map<int, std::string>> creatureSurfacesPaths;
    std::map<int, std::map<int, std::string>> playerSurfacesPaths;
    std::map<int, std::map<int, std::string>> attackSurfacesPaths;
    std::map<int, std::map<int, std::string>> stateSurfacesPaths;
    std::map<int, std::string> itemSurfacesPaths;
    std::string gameFrameSurface;
    std::string worldSurface;
    std::string goldSurface;
    std::string life_bar;
    std::string black_bar;
    std::string mana_bar;
    std::string experience_bar;

private:
    //cargadores de rutas a imagenes
    void loadCreaturePaths();
    void loadNpcPaths();
    void loadPlayerPaths();
    void loadItemPaths();
    void loadAttackPaths();
    void loadEquippedPaths();
    void loadAnimatedPaths();
    void loadStatePaths();
    void loadRestOfPaths();
};


#endif //ARGENTUM_IMAGE_PATH_CONTAINER_H
