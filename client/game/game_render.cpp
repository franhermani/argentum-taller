#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "game_render.h"
#include <iostream>
#include <exception>
#include <string>
#include <chrono>
#include <unistd.h>
#include "../client.h"
#include <stdio.h>
#include <stdlib.h>
#include "../sdl/texture.h"
#include "vector"
#include "map"
#include <utility>
#include <SDL2/SDL_ttf.h>
#include "../sdl/window.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"
#include "../../common/defines/states.h"
#include "exception.h"
#include "../sdl/exception.h"
#include "../../common/defines/attacks.h"

#define WAIT_TIME_FOR_WORLD_TO_UPDATE 60
#define WAIT_TIME_FOR_FIRST_SERVER_UPDATE 500

GameRender::GameRender(const int screenWidth, const int screenHeight,
        MapMonitor& mapMonitor) :
                       screenWidth(screenWidth), screenHeight(screenHeight),
                       mapMonitor(mapMonitor),
                       window(screenWidth, screenHeight),
                       surfacesManager(window) {
    init();
    surfacesManager.loadSurfacePaths();
    keepRunning = true;
}

GameRender::~GameRender() {
    Mix_FreeChunk(swordSound);
    Mix_FreeChunk(explosionSound);
    Mix_FreeMusic(music);
    Mix_Quit();
    SDL_Quit();
}

int GameRender::init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLException(
                "\nError al inicializar video de sdl", SDL_GetError());
    }
    initMusic();
    return true;
}

void GameRender::initMusic() {
    int flags = MIX_INIT_FLAC;
    int result = 0;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
    static const char* path_sword = "../client/resources/audio/sword.wav";
    static const char* path_explosion = "../client/resources/audio/explosion.wav";
    swordSound = Mix_LoadWAV(path_sword);
    if (swordSound == NULL) {
        std::cout << "Error: Could not load .wav file: " << path_sword << std::endl;
    }
    explosionSound = Mix_LoadWAV(path_explosion);
    if (explosionSound == NULL) {
        std::cout << "Error: Could not load .wav file: " << path_explosion << std::endl;
    }
    static const char* path_music = "../client/resources/audio/got.mp3";
    music = Mix_LoadMUS(path_music);
    if (music == NULL) {
        std::cout << "Error: Could not load .mp3 file: " << path_music << std::endl;
    }
    Mix_PlayMusic(music, -1);
}

void GameRender::renderPlayers(std::vector<player_t>& players) {
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {
        int state = it->state;
        if (state == STATE_NORMAL)
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager(*it));
        else
            window.renderMapObject(it->pos.x, it->pos.y,
                                   surfacesManager(it->state, it->orientation));
    }
}

void GameRender::renderPlayerInfo(std::map<int,float>& percentages, int level) {
    Surface* level_surface = surfacesManager.
            getTextSurface(std::to_string(level));
    window.renderPlayerInfo(current_world.percentages,
            surfacesManager.infoSurfacesMap, level_surface);
}


void GameRender::renderCreatures(std::vector<creature_t>& creatures) {
    for (auto it = std::begin(creatures);
         it != std::end(creatures); ++it) {
        int state = it->state;
        int orientation = it -> orientation;
        if (state == STATE_NORMAL)
            window.renderMapObject(it->pos.x, it->pos.y,
                    surfacesManager(*it));
        else {
            window.renderMapObject(it->pos.x, it->pos.y,
                    surfacesManager(state, orientation));
        }

    }
}



void GameRender::renderNpcs(std::vector<npc_t>& npcs) {
    surfacesManager.createNecessaryNpcs(npcs);
    for (auto it = std::begin(npcs);
         it != std::end(npcs); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                surfacesManager.npcSurfacesMap[it->type][it->orientation]);
    }
}


void GameRender::renderEquippedList(player_t& player) {
    std::vector<uint8_t> equipped_items {player.weapon, player.armor,
                                     player.shield, player.helmet};
    surfacesManager.createNecessaryFrameItems(equipped_items);
    window.renderEquipped(player, surfacesManager.itemSurfacesMap);
}


void GameRender::renderAttacks(std::vector<attack_t>& attacks) {
    for (auto it = std::begin(attacks);
         it != std::end(attacks); ++it) {
        if (it->sound == SWORD_STRIKE) {
            if (Mix_PlayChannel(0, swordSound, 0) == -1){
                std::cout << "Error: Could not play wav file  on channel "
                          << 0 << std::endl;
            }
        }
        else if (it->sound == EXPLOSION) {
            if (Mix_PlayChannel(0, explosionSound, 0) == -1){
                std::cout << "Error: Could not play wav file  on channel "
                          << 0 << std::endl;
            }
        }
        window.renderMapObject(it->pos.x, it->pos.y,
                surfacesManager(*it));
    }
}


void GameRender::renderItems(std::vector<item_t> &items) {
    for (auto it = std::begin(items);
         it != std::end(items); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager(*it));
    }
}

void GameRender::renderGolds(std::vector<gold_t> &golds) {
    for (auto it = std::begin(golds);
         it != std::end(golds); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager.goldSurface);
    }
}

void GameRender::renderWorld(position_t position) {
    window.renderWorld(surfacesManager.worldSurface,
        position, mapDimensions[0], mapDimensions[1]);
}

void GameRender::renderGameFrame() {
    window.renderGameFrame(surfacesManager.gameFrameSurface);
}

void GameRender::renderInventory(std::vector<uint8_t>& inventory) {
    surfacesManager.createNecessaryFrameItems(inventory);
    //TODO QUE PASA ACA?? SE ITERA AL PEDO? FIXEAR
    for (auto it = std::begin(inventory);
         it != std::end(inventory); ++it) {
        window.renderInventory(inventory,
                         surfacesManager.itemSurfacesMap);
    }
}

void GameRender::renderEquipped(std::vector<player_t>& players) {
    // todo el create necesary no deberia ser para cada uno?
    //sino podemos crear algo par aun fantasma. osea al pedo
    surfacesManager.createNecessaryEquipped(players);
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {

        //TRY CATCH A   CA
        if (it->state == STATE_GHOST) continue;
        if (it->armor != NO_ITEM_EQUIPPED)
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager.equippedWeaponSurfacesMap[it->armor][it->orientation]);
        if (it->shield != NO_ITEM_EQUIPPED)
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager.equippedWeaponSurfacesMap[it->shield][it->orientation]);
        if (it->weapon != NO_ITEM_EQUIPPED)
            window.renderMapObject(it->pos.x, it->pos.y,
                                   surfacesManager.equippedWeaponSurfacesMap[it->weapon][it->orientation]);

    }
}

void GameRender::renderInventoryGolds(uint16_t quantity) {
    window.renderInventoryGolds(surfacesManager.goldSurface,
            surfacesManager.getTextSurface(std::to_string(quantity)));
}

//TODO A ESTA NUNCA LA LLAMAN BORRAR"!!"#1231231231231C-.-.-SA.CZXCZMXNCZM,X
void GameRender::setTilesSize(int width,int height) {
    blocksWidth = width;
    blocksHeight = height;
    window.setTilesSize(width,height);
}

void GameRender::renderList(list_t list) {
    surfacesManager.createNecessaryListItems(list.items);
    std::vector<Surface*> surfaces;
    for (auto it = std::begin(list.items); it != std::end(list.items); ++it) {
         surfaces.push_back(surfacesManager.itemSurfacesMap[it->type]);
    }
    window.renderList(surfaces);
    if (list.show_price) {
        std::vector<Surface*> price_surfaces;
        for (auto it = std::begin(list.items);
        it != std::end(list.items); ++it) {
            price_surfaces.push_back(surfacesManager.getTextSurface(
                    std::to_string(it->price)));
        }
        window.renderListPrices(price_surfaces);
    } else {
        Surface* quantity = surfacesManager.getTextSurface(
                std::to_string(list.gold_quantity));
        window.renderListGold(surfacesManager.goldSurface, quantity);
    }
}

void GameRender::toggleFullscreen() {
    window.toggleFullscreen();
}

void GameRender::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;
    std::this_thread::sleep_for(ms(WAIT_TIME_FOR_FIRST_SERVER_UPDATE));
    blocksWidth = mapMonitor.getPlayerVisionWidth();
    blocksHeight = mapMonitor.getPlayerVisionHeight();
    mapDimensions = mapMonitor.getDimensions();
    window.setTilesSize(blocksWidth,blocksHeight);


    while (keepRunning) {
        auto start = clock::now();


        renderGameFrame();
        current_world = mapMonitor.getCurrentWorld();
        renderWorld(current_world.main_player.pos);
        renderItems(current_world.items);
        renderPlayers(current_world.players);
        renderNpcs(current_world.npcs);
        renderCreatures(current_world.creatures);
        renderInventory(current_world.player_info.inventory.items);
        renderInventoryGolds(current_world.player_info.actual_gold);
        renderEquipped(current_world.players);
        renderEquippedList(current_world.main_player);
        renderAttacks(current_world.attacks);
        renderGolds(current_world.golds);
        renderPlayerInfo(current_world.percentages,
                current_world.main_player.level);
        if (mapMonitor.isInteracting()) renderList(current_world.list);
        window.UpdateWindowSurface();
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = WAIT_TIME_FOR_WORLD_TO_UPDATE - elapsed;
        std::this_thread::sleep_for(ms(time_to_sleep));
    }
}

int GameRender::getInventoryItemByPosition(int x, int y) {
    int inventory_length = current_world.player_info.inventory.length;
    int position = window.getRenderedItemIndexByPosition(x, y,
            inventory_length);
    if (position < 0) throw ItemException(
            "El inventario no tiene items en la posicion clickeada");
    if (inventory_length < position) throw
            ItemException("El inventario ya no tiene ese item");
    return current_world.player_info.inventory.items[position];
}
int GameRender::getEquippedTypeByPosition(int x, int y) {
    int type = window.getRenderedEquipedTypeByPosition(x, y);
    if (type < 0) throw ItemException(
            "No hay nada equipado en esa posicion");
    return window.getRenderedEquipedTypeByPosition(x, y);
}




int GameRender::getListItemByPosition(int x, int y) {
    int list_length = current_world.list.num_items;
    int position = window.getRenderedListIndexByPosition(x, y, list_length);

    if (position < 0) throw ItemException(
                "la lista no tiene items en la posicion clickeada");
    if (list_length < position) throw
                ItemException("la lista ya no tiene ese item");
    return current_world.list.items[position].type;
}

int GameRender::isClickingListItems(int x, int y) {
    return window.isClickingListItems(x, y);
}

int GameRender::isClickingListGold(int x, int y) {
    return window.isClickingListGold(x, y);
}
int GameRender::isClickingInventoryItems(int x, int y) {
    return window.isClickingInventoryItems(x, y);
}

int GameRender::isClickingInventoryGold(int x, int y) {
    return window.isClickingInventoryGold(x, y);
}


void GameRender::stop() {
    keepRunning = false;
}

bool GameRender::isDead()  {
    return (! isRunning);
}
