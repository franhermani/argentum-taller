#include <SDL2/SDL.h>
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
#include "exception.h"
#include "../sdl/exception.h"
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
    SDL_Quit();
}

int GameRender::init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLException(
                "\nError al inicializar video de sdl", SDL_GetError());
    }
    return true;
}


void GameRender::renderTerrain(std::vector<std::vector<Terrain>>& matrix) {
    surfacesManager.createNecessaryTerrains(matrix);
    window.renderTerrain(matrix, surfacesManager.terrainSurfacesMap);
}


void GameRender::renderPlayers(std::vector<player_t>& players) {
    surfacesManager.createNecessaryPlayers(players);
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                surfacesManager.
                playerSurfacesMap[it->race_type][it->orientation]);
    }
}

void GameRender::renderPlayerInfo(std::map<int,float>& percentages, int level) {
    Surface* level_surface = surfacesManager.getTextSurface(std::to_string(level));
    window.renderPlayerInfo(current_world.percentages,
                            surfacesManager.infoSurfacesMap, level_surface);
}


void GameRender::renderCreatures(std::vector<creature_t>& creatures) {
    surfacesManager.createNecessaryCreatures(creatures);
    for (auto it = std::begin(creatures);
         it != std::end(creatures); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                surfacesManager.
                creatureSurfacesMap[it->type][it->orientation]);
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


void GameRender::renderEquipped(player_t& player) {
    std::vector<uint8_t> equipped_items {player.weapon, player.armor,
                                     player.shield, player.helmet};
    surfacesManager.createNecessaryFrameItems(equipped_items);
    window.renderEquipped(player, surfacesManager.itemSurfacesMap);
}


void GameRender::renderItems(std::vector<item_t> &items) {
    surfacesManager.createNecessaryItems(items);
    for (auto it = std::begin(items);
         it != std::end(items); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager.itemSurfacesMap[it->type]);
    }
}

void GameRender::renderGolds(std::vector<gold_t> &golds) {
    for (auto it = std::begin(golds);
         it != std::end(golds); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               surfacesManager.goldSurface);
    }
}

void GameRender::renderGameFrame() {
    window.renderGameFrame(surfacesManager.gameFrameSurface);
}

void GameRender::renderInventory(std::vector<uint8_t>& inventory) {
    surfacesManager.createNecessaryFrameItems(inventory);
    for (auto it = std::begin(inventory);
         it != std::end(inventory); ++it) {
        window.renderInventory(inventory,
                         surfacesManager.itemSurfacesMap);
    }
}

void GameRender::renderInventoryGolds(uint16_t quantity) {
    window.renderInventoryGolds(surfacesManager.goldSurface,
            surfacesManager.getTextSurface(std::to_string(quantity)));
}


void GameRender::setTilesSize(int width,int height) {
    blocksWidth = width;
    blocksHeight = height;
    window.setTilesSize(width,height);
}

void GameRender::renderText() {

}


void GameRender::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;
    std::this_thread::sleep_for(ms(WAIT_TIME_FOR_FIRST_SERVER_UPDATE));
    blocksWidth = mapMonitor.getPlayerVisionWidth();
    blocksHeight = mapMonitor.getPlayerVisionHeight();
    window.setTilesSize(blocksWidth,blocksHeight);


    while (keepRunning) {
        auto start = clock::now();

        renderGameFrame();
        current_world = mapMonitor.getCurrentWorld();
        renderTerrain(current_world.terrains);
        renderItems(current_world.items);
        renderPlayers(current_world.players);
        renderNpcs(current_world.npcs);
        renderCreatures(current_world.creatures);
        renderInventory(current_world.player_info.inventory.items);
        renderInventoryGolds(current_world.player_info.actual_gold);
        renderEquipped(current_world.main_player);
        renderGolds(current_world.golds);
        renderPlayerInfo(current_world.percentages, current_world.main_player.level);
        //renderList();
        //window.renderListGold();
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


int GameRender::getListItemByPosition(int x, int y) {
    //TODO cuando se reciba la lista de items de banquero/merchanat descomentar
    //size_t inventory_length = current_world.player_info.list.length;
    /*int position = window.getRenderedListIndexByPosition(x, y, inventory_length);
    if (position < 0) throw ItemException(
                "la lista no tiene items en la posicion clickeada");
    if (current_world.player_info.inventory.length < position) throw
                ItemException("la lista ya no tiene ese item");
    //return current_world.player_info.inventory.items[position];
     */
    return 1;
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
