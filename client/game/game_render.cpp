#include <SDL2/SDL.h>
#include "game_render.h"
#include <string>
#include <chrono>
#include <unistd.h>
#include "vector"
#include "map"
#include <utility>
#include "exception.h"
#include "../sdl/exception.h"
#define NUMBER_OF_ITERATIONS_FOR_ANIMATION 5
#define WAIT_TIME_FOR_WORLD_TO_UPDATE 60

#define WAIT_TIME_FOR_FIRST_SERVER_UPDATE 500

GameRender::GameRender(const int screenWidth, const int screenHeight,
        MapMonitor& mapMonitor, std::string username) :
        screenWidth(screenWidth), screenHeight(screenHeight),
        mapMonitor(mapMonitor),
        username(username),
        window(screenWidth, screenHeight),
        imagesManager(window) {
    init();
    imagesManager.loadSurfacePaths();
    keepRunning = true;
}

GameRender::~GameRender() {
    SDL_Quit();
}

int GameRender::init() {
    return true;
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
        current_world = mapMonitor.getCurrentWorld();
        renderGame();
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = WAIT_TIME_FOR_WORLD_TO_UPDATE - elapsed;
        std::this_thread::sleep_for(ms(time_to_sleep));
    }
}

void GameRender::renderGame() {
    for (int i=0; i<NUMBER_OF_ITERATIONS_FOR_ANIMATION; i++) {
        renderGameFrame();
        renderWorld(current_world.main_player.pos);
        renderItems(current_world.items);
        renderGolds(current_world.golds);
        renderPlayers(current_world.players, i);
        renderNpcs(current_world.npcs);
        renderCreatures(current_world.creatures);
        renderInventory(current_world.player_info.inventory.items);
        renderInventoryGolds(current_world.player_info.actual_gold);
        renderEquipped(current_world.players);
        renderEquippedList(current_world.main_player);
        renderAttacks(current_world.attacks);
        renderPlayerInfo(current_world.percentages,
                         current_world.main_player.level);
        if (mapMonitor.isInteracting()) renderList(current_world.list);
        window.UpdateWindowSurface();
        using ms = std::chrono::milliseconds;
        std::this_thread::sleep_for(ms(WAIT_TIME_FOR_WORLD_TO_UPDATE/
                                    NUMBER_OF_ITERATIONS_FOR_ANIMATION));
    }
}

void GameRender::renderPlayerInfo(std::map<int,float>& percentages, int level) {
    Surface* level_surface = imagesManager(
            std::to_string(level));
    Surface* name_surface = imagesManager(username);
    window.renderPlayerInfo(current_world.percentages,
                            imagesManager.infoSurfacesMap, level_surface, name_surface);
}


void GameRender::renderCreatures(std::vector<creature_t>& creatures) {
    for (auto it = std::begin(creatures);
         it != std::end(creatures); ++it) {
        if (it->state == STATE_NORMAL) {
            window.renderMapObject(it->pos.x, it->pos.y,
                                   imagesManager(*it));
            window.renderMapObjectLifeBar(it->pos.x, it->pos.y,
                                          imagesManager.infoSurfacesMap[LIFE],
                                          (it->actual_life/(float) it->max_life));
        } else {
            window.renderMapObject(it->pos.x, it->pos.y,
                                   imagesManager(it->state, it->orientation));
        }
    }
}

void GameRender::renderNpcs(std::vector<npc_t>& npcs) {
    for (auto it = std::begin(npcs);
         it != std::end(npcs); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               imagesManager(*it));
    }
}


void GameRender::renderEquippedList(player_t& player) {
    std::vector<uint8_t> equipped_items {player.weapon, player.armor,
                                     player.shield, player.helmet};
    imagesManager.createNecessaryFrameItems(equipped_items);
    window.renderEquipped(player, imagesManager.itemSurfacesMap);
}


void GameRender::renderAttacks(std::vector<attack_t>& attacks) {
    for (auto it = std::begin(attacks);
         it != std::end(attacks); ++it) {
        soundManager.playSound((soundType) it->sound);
        window.renderMapObject(it->pos.x, it->pos.y,
                               imagesManager(*it));
    }
}


void GameRender::renderItems(std::vector<item_t> &items) {
    for (auto it = std::begin(items);
         it != std::end(items); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               imagesManager(it->type));
    }
}

void GameRender::renderGolds(std::vector<gold_t> &golds) {
    for (auto it = std::begin(golds);
         it != std::end(golds); ++it) {
        window.renderMapObject(it->pos.x, it->pos.y,
                               imagesManager.goldSurface);
    }
}

void GameRender::renderWorld(position_t position) {
    window.renderWorld(imagesManager.worldSurface,
                       position, mapDimensions[0], mapDimensions[1]);
}

void GameRender::renderGameFrame() {
    window.renderGameFrame(imagesManager.gameFrameSurface);
}

void GameRender::renderInventory(std::vector<uint8_t>& inventory) {
    imagesManager.createNecessaryFrameItems(inventory);
    window.renderInventory(inventory,
                           imagesManager.itemSurfacesMap);
}

void GameRender::renderPlayers(std::vector<player_t>& players, int iteration) {
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {
        stateType state = it->state;
        if (state == STATE_NORMAL) {
            window.renderMapObject(it->pos.x, it->pos.y,
                                   imagesManager(*it));
        } else {
            try {
                window.renderAnimatedMapObject(it->pos.x, it->pos.y,
                                               imagesManager.animation(state), iteration);
            } catch (SurfaceExistanceException& e) {
                window.renderMapObject(it->pos.x, it->pos.y,
                                       imagesManager(it->state, it->orientation));
            }
        }
    }
}

void GameRender::renderSingleEquipped(player_t& player, int part) {
    try {
        window.renderMapObject(player.pos.x, player.pos.y,
                imagesManager.getEquipped(part, player.orientation));
    } catch (SurfaceExistanceException& e) {
        return;
    }
}

void GameRender::renderEquipped(std::vector<player_t>& players) {
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {
        if (it->state == STATE_GHOST) continue;
        renderSingleEquipped(*it, it->armor);
        renderSingleEquipped(*it, it->shield);
        renderSingleEquipped(*it, it->weapon);
        renderSingleEquipped(*it, it->helmet);
    }
}

void GameRender::renderInventoryGolds(uint16_t quantity) {
    window.renderInventoryGolds(imagesManager.goldSurface,
                                imagesManager(std::to_string(quantity)));
}



void GameRender::renderList(list_t list) {
    std::vector<Surface*> surfaces = imagesManager(list.items);
    window.renderList(surfaces);
    if (list.show_price) {
        std::vector<Surface*> price_surfaces;
        for (auto it = std::begin(list.items);
        it != std::end(list.items); ++it) {
            price_surfaces.push_back(imagesManager(
                    std::to_string(it->price) + " "));
        }
        window.renderListPrices(price_surfaces);
    } else {
        Surface* quantity = imagesManager(
                std::to_string(list.gold_quantity));
        window.renderListGold(imagesManager.goldSurface, quantity);
    }
}

void GameRender::toggleFullscreen() {
    window.toggleFullscreen();
}

void GameRender::toggleMusic() {
    soundManager.toggleMusic();
}

void GameRender::toggleSound() {
    soundManager.toggleSound();
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
