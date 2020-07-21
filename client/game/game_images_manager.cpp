
#include "game_images_manager.h"
#include "iostream"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"
#include "../../common/defines/attacks.h"
#include "../../common/defines/states.h"
#include "../sdl/exception.h"


GameImagesManager::GameImagesManager(SDLWindow& window) : window(window) {
    mainFont = TTF_OpenFont("../client/resources/fonts/goudy.ttf", 100);
    if (mainFont == NULL) {
        throw SDLException("\nError al cargar font de surfaces",
                           SDL_GetError());
    }
    mainColor = {255, 255,255};
}
GameImagesManager::~GameImagesManager(){
    for (auto const& surface : infoSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : textSurfaces) {
        delete surface.second;
    }
    for (auto const& surface : itemSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : animatedStateMap) {
        delete surface.second;
    }
    for (auto const& orientations : creatureSurfacesMap) {
        for (auto const& surface : orientations.second)  delete surface.second;
    }
    for (auto const& orientations : stateSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : playerSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : npcSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : attackSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }

    delete goldSurface;
    delete gameFrameSurface;
    delete worldSurface;
    TTF_CloseFont(mainFont);
}


Surface* GameImagesManager::operator()(std::string text) {
    if (textSurfaces.find(text)
        == textSurfaces.end()) {
        Surface* surface = new Surface(text, window, mainFont, mainColor);
        //guardamos para luego liberar memoria
        textSurfaces.insert({text, surface});
        return surface;
    }
    return textSurfaces[text];
}


Surface* GameImagesManager::operator()(stateType state, int orientation) {
    if (stateSurfacesMap[state].find(orientation)
        == stateSurfacesMap[state].end()) {
        Surface* surface = new Surface(
                pathContainer.stateSurfacesPaths[state][orientation], window, 1);
        stateSurfacesMap[state].insert({orientation, surface});
        return surface;
    } else {
        return stateSurfacesMap[state][orientation];
    }
}


Surface* GameImagesManager::operator()(attack_t& attack) {
    int type = attack.type;
    int orientation = attack.orientation;
    if (attackSurfacesMap[type].find(orientation)
        == attackSurfacesMap[type].end()) {
        Surface* surface = new Surface(
                pathContainer.attackSurfacesPaths[type][orientation], window, 1);
        attackSurfacesMap[type].insert({orientation, surface});
        return surface;
    } else {
        return attackSurfacesMap[type][orientation];
    }
}


Surface* GameImagesManager::operator()(npc_t& npc) {
    int type = npc.type;
    int orientation = npc.orientation;
    if (npcSurfacesMap[type].find(orientation)
        == npcSurfacesMap[type].end()) {
        Surface* surface = new Surface(
                pathContainer.npcSurfacesPaths[type][orientation], window, 1);
        npcSurfacesMap[type].insert({orientation, surface});
        return surface;
    } else {
        return npcSurfacesMap[type][orientation];
    }
}

Surface* GameImagesManager::operator()(creature_t& creature) {
    int type = creature.type;
    int orientation = creature.orientation;
    if (creatureSurfacesMap[type].find(orientation)
        == creatureSurfacesMap[type].end()) {
        Surface *surface = new Surface(
                pathContainer.creatureSurfacesPaths[type][orientation], window, 1);
        creatureSurfacesMap[type].insert({orientation, surface});
        return surface;
    } else {
        return creatureSurfacesMap[type][orientation];
    }
}


Surface* GameImagesManager::operator()(player_t& player) {
    int race = player.race_type;
    int orientation = player.orientation;
    if (playerSurfacesMap[race].find(orientation)
        == playerSurfacesMap[race].end()) {
        Surface* surface = new Surface(
                pathContainer.playerSurfacesPaths[race][orientation], window, 1);
        playerSurfacesMap[race].insert({orientation, surface});
        return surface;
    } else {
        return playerSurfacesMap[race][orientation];
    }
}


Surface* GameImagesManager::operator()(int item_type) {
    if (itemSurfacesMap.find(item_type)
        == itemSurfacesMap.end()) {
        Surface* surface = new Surface(
                pathContainer.itemSurfacesPaths[item_type], window, 1);
        itemSurfacesMap.insert({item_type, surface});
        return surface;
    } else {
        return itemSurfacesMap[item_type];
    }
}


std::vector<Surface*> GameImagesManager::operator()(
        std::vector<list_item_t> items) {
    std::vector<Surface*> surfaces;
    for (auto& item: items) {
        int type = item.type;
        Surface* surface;
        if (itemSurfacesMap.find(type)
            == itemSurfacesMap.end()) {
            surface = new Surface(
                    pathContainer.itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        } else {
            surface = itemSurfacesMap[type];
        }
        surfaces.push_back(surface);
    }
    return surfaces;
}

Surface* GameImagesManager::animation(stateType state) {
    if (animatedStateMap.find(state)
        == animatedStateMap.end()) {
        if (pathContainer.animatedStatePaths.find(state)
            == pathContainer.animatedStatePaths.end()) {
            throw SurfaceExistanceException("Surface no existente");
        } else {
            Surface* surface = new Surface(
                    pathContainer.animatedStatePaths[state], window, 1);
            animatedStateMap.insert({state, surface});
            return surface;
        }
    }
    return animatedStateMap[state];
}

Surface* GameImagesManager::getEquipped(
        int weapon, int orientation) {
    if (pathContainer.equippedWeaponSurfacesPaths.find(weapon)
        == pathContainer.equippedWeaponSurfacesPaths.end())
        throw SurfaceExistanceException("Surface no existente");
    if (equippedWeaponSurfacesMap[weapon].find(orientation)
            == equippedWeaponSurfacesMap[weapon].end()) {
            Surface* surface = new Surface(
                    pathContainer.equippedWeaponSurfacesPaths[weapon][orientation],
                    window, 1);
            equippedWeaponSurfacesMap[weapon].insert({orientation, surface});
            return surface;
    }
    return equippedWeaponSurfacesMap[weapon][orientation];
}

void GameImagesManager::createNecessaryFrameItems(
        std::vector<uint8_t>& items) {
    for (auto& type: items) {
        if (pathContainer.itemSurfacesPaths.find(type)
           == pathContainer.itemSurfacesPaths.end()) continue;
        if (itemSurfacesMap.find(type)
            == itemSurfacesMap.end()) {
            Surface* surface = new Surface(
                    pathContainer.itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        }
    }
}



void GameImagesManager::initCreatures() {

    std::map<int, Surface*> skeleton_surfaces;
    std::map<int, Surface*> zombie_surfaces;
    std::map<int, Surface*> goblin_surfaces;
    creatureSurfacesMap = {{SKELETON, skeleton_surfaces},
                           {ZOMBIE,   zombie_surfaces},
                           {GOBLIN,   goblin_surfaces}
    };
}

void GameImagesManager::initEquipped() {

    std::map<int, Surface*> baculo_nudoso_surfaces;
    std::map<int, Surface*> arco_compuesto_surfaces;
    std::map<int, Surface*> arco_simple_surfaces;
    std::map<int, Surface*> baculo_engarzado_surfaces;
    std::map<int, Surface*> flauta_elfica_surfaces;
    std::map<int, Surface*> vara_fresno_surfaces;
    std::map<int, Surface*> martilo_surfaces;
    std::map<int, Surface*> hacha_surfaces;
    std::map<int, Surface*> espada_surfaces;
    std::map<int, Surface*> armadura_placas_surfaces;
    std::map<int, Surface*> armadura_cuero_surfaces;
    std::map<int, Surface*> tunica_azul_surfaces;
    std::map<int, Surface*> escudo_hierro_surfaces;
    std::map<int, Surface*> escudo_tortuga_surfaces;
    std::map<int, Surface*> capucha_surfaces;
    std::map<int, Surface*> casco_hierro_surfaces;
    std::map<int, Surface*> sombrero_magico_surfaces;
    equippedWeaponSurfacesMap = {
            {ESPADA, espada_surfaces},
            {HACHA, hacha_surfaces},
            {MARTILLO, martilo_surfaces},
            {VARA_FRESNO, vara_fresno_surfaces},
            {FLAUTA_ELFICA, flauta_elfica_surfaces},
            {BACULO_NUDOSO, baculo_nudoso_surfaces},
            {BACULO_ENGARZADO,
                    baculo_engarzado_surfaces},
            {ARCO_SIMPLE, arco_simple_surfaces},
            {ARCO_COMPUESTO,
                    arco_compuesto_surfaces},
            {ARMADURA_PLACAS, armadura_placas_surfaces},
            {ARMADURA_CUERO, armadura_cuero_surfaces},
            {ESCUDO_TORTUGA, escudo_tortuga_surfaces},
            {ESCUDO_HIERRO, escudo_hierro_surfaces},
            {TUNICA_AZUL, tunica_azul_surfaces},
            {CASCO_HIERRO, casco_hierro_surfaces},
            {CAPUCHA, capucha_surfaces},
            {SOMBRERO_MAGICO, sombrero_magico_surfaces}
    };
}


void GameImagesManager::initNpc() {

    std::map<int, Surface*> priest_surfaces;
    std::map<int, Surface*> merchant_surfaces;
    std::map<int, Surface*> banker_surfaces;
    npcSurfacesMap = {{PRIEST, priest_surfaces},
                      {MERCHANT, merchant_surfaces},
                      {BANKER, banker_surfaces}
    };
}



void GameImagesManager::initAttack() {
    std::map<int, Surface*> multiple_arrow_surfaces;
    std::map<int, Surface*> single_arrow_surfaces;
    std::map<int, Surface*> missile_surfaces;
    std::map<int, Surface*> magic_arrow_surfaces;
    std::map<int, Surface*> explosion_spell_surfaces;
    std::map<int, Surface*> heal_spell_surfaces;
    std::map<int, Surface*> melee_surfaces;
    std::map<int, Surface*> no_weapon_melee_surfaces;
    attackSurfacesMap = {{MULTIPLE_ARROW, multiple_arrow_surfaces},
                         {SINGLE_ARROW,   single_arrow_surfaces},
                         {MELEE, melee_surfaces},
                         {MAGIC_ARROW_SPELL, magic_arrow_surfaces},
                         {HEAL_SPELL, heal_spell_surfaces},
                         {MISSILE_SPELL, missile_surfaces},
                         {EXPLOSION_SPELL, explosion_spell_surfaces},
                         {NO_WEAPON_MELEE, no_weapon_melee_surfaces}
    };
}

void GameImagesManager::initPlayers() {
    //JUGADORES

    std::map<int, Surface*> human_surfaces;
    std::map<int, Surface*> elf_surfaces;
    std::map<int, Surface*> dwarf_surfaces;
    std::map<int, Surface*> gnome_surfaces;
    playerSurfacesMap = {{HUMAN, human_surfaces},
                         {ELF, elf_surfaces},
                         {DWARF, dwarf_surfaces},
                         {GNOME, gnome_surfaces}};
    std::map<int, Surface*> ghostSurfacesMap;
    std::map<int, Surface*> reviveSurfacesMap;
    std::map<int, Surface*> meditateSurfacesMap;
    std::map<int, Surface*> dyingSurfacesMap;
    stateSurfacesMap = {
            {STATE_GHOST, ghostSurfacesMap},
            {STATE_REVIVING, reviveSurfacesMap},
            {STATE_MEDITATING, meditateSurfacesMap},
            {STATE_DYING, dyingSurfacesMap}
    };
}

void GameImagesManager::loadSurfacePaths() {
    initCreatures();
    initNpc();
    initPlayers();
    initAttack();
    initEquipped();
    initFrame();
}


void GameImagesManager::initFrame() {
    gameFrameSurface = new Surface(pathContainer.gameFrameSurface, window, 0);
    worldSurface = new Surface(pathContainer.worldSurface, window, 0);
    goldSurface = new Surface(
            pathContainer.goldSurface, window, 1);
    Surface* life_bar = new Surface(pathContainer.life_bar,
            window, 0);
    Surface* black_bar = new Surface(pathContainer.black_bar, window, 0);
    Surface* mana_bar = new Surface(pathContainer.mana_bar, window, 0);
    Surface* experience_bar = new Surface(pathContainer.experience_bar, window, 0);

    infoSurfacesMap = {
            {LIFE, life_bar},
            {MANA, mana_bar},
            {EXPERIENCE, experience_bar},
            {BACKGROUND,black_bar}
    };
}
