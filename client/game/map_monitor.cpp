
#include "map_monitor.h"
#include <vector>
#include <iostream>
#include <utility>

MapMonitor::MapMonitor() {}

MapMonitor::~MapMonitor() {}

//inicializa matriz
void MapMonitor::initialize(int username_id,
        std::vector<int>& blocks_around, matrix_t& received_matrix,
        npcs_t& npcs) {
    std::unique_lock<std::mutex> lk(m);
    map.initialize(username_id, blocks_around, received_matrix, npcs);
}

//actualiza el vector de jugadores
void MapMonitor::updateWorld(world_t receivedWorld, list_t list) {
    std::unique_lock<std::mutex> lk(m);
    map.updateWorld(std::move(receivedWorld), std::move(list));
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

std::vector<int> MapMonitor::getItemStandingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getItemStandingAt());
}

std::vector<int> MapMonitor::getGoldStandingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getGoldStandingAt());
}

client_world_t MapMonitor::getCurrentWorld() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getCurrentWorld());
}



void MapMonitor::interact() {
    std::unique_lock<std::mutex> lk(m);
    map.interact();
}
void MapMonitor::uninteract() {
    std::unique_lock<std::mutex> lk(m);
    map.uninteract();
}

int MapMonitor::isInteracting() {
    std::unique_lock<std::mutex> lk(m);
    return map.isInteracting();
}
