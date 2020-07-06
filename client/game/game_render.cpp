#include <SDL2/SDL.h>
#include "game_render.h"
#include <iostream>
#include <exception>
#include <chrono>
#include <unistd.h>
#include "../client.h"
#include "../sdl/texture.h"
#include "vector"
#include "map"
#include <utility>
#include "../sdl/window.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"
#include "exception.h"
#include "../sdl/exception.h"

GameRender::GameRender(const int screenWidth, const int screenHeight,
        MapMonitor& mapMonitor) :
                       screenWidth(screenWidth), screenHeight(screenHeight),
                       mapMonitor(mapMonitor),
                       window(screenWidth, screenHeight), surfacesManager(window) {
    init();
    surfacesManager.loadSurfacePaths();
}

GameRender::~GameRender() {
    SDL_Quit();
}

int GameRender::init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLException("Error al inicializar video de sdl", SDL_GetError());
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
        window.renderNpc(it->pos_x, it->pos_y,
                         surfacesManager.playerSurfacesMap[it->race_type][it->orientation]);
    }
}




void GameRender::renderCreatures(std::vector<creature_t>& creatures) {
    surfacesManager.createNecessaryCreatures(creatures);
    for (auto it = std::begin(creatures);
         it != std::end(creatures); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                         surfacesManager.creatureSurfacesMap[it->type][it->orientation]);
    }
}



void GameRender::renderNpcs(std::vector<npc_t>& npcs) {
    surfacesManager.createNecessaryNpcs(npcs);
    for (auto it = std::begin(npcs);
         it != std::end(npcs); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                         surfacesManager.npcSurfacesMap[it->type][it->orientation]);
    }
}




void GameRender::renderItems(std::vector<item_t> &items) {
    surfacesManager.createNecessaryItems(items);
    for (auto it = std::begin(items);
         it != std::end(items); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                         surfacesManager.floorItemSurfacesMap[it->type]);
    }
}




void GameRender::setTilesSize(int width,int height) {
    blocksWidth = width;
    blocksHeight = height;
    window.setTilesSize(width,height);
}

std::map<int, float> GameRender::getRenderablePlayerInfo() {
    std::map<int, float> playerInfo = {
            //TODO QUE ESTO LO HAGA EL MAP!
            //TODO RECIBIR EXPERIENCE max
            {LIFE, ((float) current_world.main_player.actual_life)/
                            current_world.main_player.max_life},
            {MANA, ((float) current_world.player_info.actual_mana)/
                            current_world.player_info.max_mana},
            {EXPERIENCE, ((float) current_world.player_info.actual_experience)/
                            current_world.player_info.actual_experience}
    };
    return std::move(playerInfo);
}

void GameRender::run() {
    using ms = std::chrono::milliseconds;
    std::this_thread::sleep_for(ms(500));
    blocksWidth = mapMonitor.getPlayerVisionWidth();
    blocksHeight = mapMonitor.getPlayerVisionHeight();
    window.setTilesSize(blocksWidth,blocksHeight);
    window.renderGameFrame(surfacesManager.createGameFrameSurface());

    std::vector<Surface*> inventory_items =
            {new Surface("../client/resources/images/pocion_mana_t.png",
                         window, 0),
             new Surface("../client/resources/images/armadura_cuero_t.png",
                         window, 0),
             new Surface("../client/resources/images/pocion_mana_t.png",
                         window, 0),
             new Surface("../client/resources/images/arco_compuesto_t.png",
                         window, 0),
             new Surface("../client/resources/images/pocion_mana_t.png",
                         window, 0),
             new Surface("../client/resources/images/escudo_tortuga_t.png",
                         window, 0),
             new Surface("../client/resources/images/capucha_t.png",
                         window, 0)};
    Surface* gold_surface = new Surface("../client/resources/images/gold_t.png", window, 1);
    while (keepRunning) {
        current_world = mapMonitor.getCurrentWorld();
        renderTerrain(current_world.terrains);
        renderPlayers(current_world.players);
        renderNpcs(current_world.npcs);
        renderCreatures(current_world.creatures);
        //simulamos inventario recibido de server
        window.renderInventory(inventory_items);
        //cuando lleguen los items del server los renderizamos
        /*std::vector<item_t> floor_items;
        item_t item = {3, 2, 3};
        floor_items.push_back(item);
        item_t item2 = {1, 3, 5};
        floor_items.push_back(item2);
        item_t item3 = {5, 4, 2};
        floor_items.push_back(item3);
        renderItems(floor_items);
         */
        //simulamos un player, despues poner el posta sacado de current_world
        player_t player;
        player.shield = ESCUDO_HIERRO;
        player.armor = ARMADURA_CUERO;
        player.helmet = NO_ITEM_EQUIPPED;
        player.weapon = ARCO_COMPUESTO;
        window.renderEquipped(player, surfacesManager.floorItemSurfacesMap);
        window.renderPlayerInfo(getRenderablePlayerInfo(),
                                surfacesManager.infoSurfacesMap);
        window.renderList(inventory_items);
        window.renderInventoryGold(gold_surface);
        window.renderListGold(gold_surface);
        window.UpdateWindowSurface();
        std::this_thread::sleep_for(ms(10));
    }
}

int GameRender::getInventoryItemByPosition(int x, int y) {
    //size_t inventory_length = current_world.player_info.inventory.length;
    int position = window.getRenderedItemIndexByPosition(x, y, 7);
    if (position < 0) throw ItemException(
            "El inventario no tiene items en la posicion clickeada");
    /*if (current_world.player_info.inventory.length < position) throw
            ItemException("El inventario ya no tiene ese item");*/
    std::cout << "\n\nESTA ES LA POSITION DE INVENTARIO" << position;

//    return current_world.player_info.inventory.items[position];
    return 1;
}


int GameRender::getListItemByPosition(int x, int y) {
    //size_t inventory_length = current_world.player_info.list.length;
    int position = window.getRenderedListIndexByPosition(x, y, 7);
    if (position < 0) throw ItemException(
                "la lista no tiene items en la posicion clickeada");
    /*if (current_world.player_info.inventory.length < position) throw
                ItemException("la lista ya no tiene ese item");*/
    std::cout << "\n\nESTA ES LA POSITION DE list" << position;
    //return current_world.player_info.inventory.items[position];
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
