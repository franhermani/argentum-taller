
#include "map_monitor.h"
#include <vector>
#include <iostream>

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
