
#include "map_monitor.h"
#include <vector>
#include <iostream>
#include <utility>

MapMonitor::MapMonitor() {}

MapMonitor::~MapMonitor() {}

//inicializa matriz
void MapMonitor::initialize(int username_id,
        std::vector<int> blocks_around, matrix_t received_matrix, npcs_t npcs) {
    std::unique_lock<std::mutex> lk(m);
    //TODO CUIDADO COPIAS CAMBIAR
    map.initialize(username_id, blocks_around, received_matrix, npcs);
}

//actualiza el vector de jugadores
void MapMonitor::updateWorld(world_t receivedWorld) {
    std::unique_lock<std::mutex> lk(m);
    //TODO CUIDADO COPIAS CAMBIAR
    map.updateWorld(receivedWorld);
}


std::vector<std::vector<Terrain>> MapMonitor::getTerrains() {
    std::unique_lock<std::mutex> lk(m);
    return map.getTerrains();
}


std::vector<player_t> MapMonitor::getRenderablePlayers() {
    std::unique_lock<std::mutex> lk(m);
    return map.getRenderablePlayers();
}

std::vector<creature_t> MapMonitor::getRenderableCreatures() {
    std::unique_lock<std::mutex> lk(m);
    return map.getRenderableCreatures();
}

std::vector<item_t> MapMonitor::getRenderableItems() {
    std::unique_lock<std::mutex> lk(m);
    return map.getRenderableItems();
}

std::vector<npc_t> MapMonitor::getRenderableNpcs() {
    std::unique_lock<std::mutex> lk(m);
    return map.getRenderableNpcs();
}

int MapMonitor::getPlayerVisionWidth() {
    return map.getPlayerVisionWidth();
}
int MapMonitor::getPlayerVisionHeight() {
    return map.getPlayerVisionHeight();
}

std::vector<int> MapMonitor::getPositionLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getPositionLookingAt());
}


std::vector<int> MapMonitor::getPriestLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getPriestLookingAt());
}


std::vector<int> MapMonitor::getNpcLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getNpcLookingAt());
}
player_info_t MapMonitor::getPlayerInfo() {
    std::unique_lock<std::mutex> lk(m);
    return map.getPlayerInfo();
}

