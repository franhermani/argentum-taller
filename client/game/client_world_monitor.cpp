
#include "client_world_monitor.h"
#include <vector>
#include <iostream>
#include <utility>

ClientWorldMonitor::ClientWorldMonitor() {}

ClientWorldMonitor::~ClientWorldMonitor() {}


void ClientWorldMonitor::initialize(int username_id,
                                    std::vector<int>& blocks_around,
                                    npcs_t& npcs, std::vector<int>& map_dimensions) {
    std::unique_lock<std::mutex> lk(m);
    map.initialize(username_id, blocks_around, npcs, map_dimensions);
}

void ClientWorldMonitor::updateWorld(world_t receivedWorld, list_t list) {
    std::unique_lock<std::mutex> lk(m);
    map.updateWorld(std::move(receivedWorld), std::move(list));
}

int ClientWorldMonitor::getPlayerVisionWidth() {
    return map.getPlayerVisionWidth();
}


int ClientWorldMonitor::getPlayerVisionHeight() {
    return map.getPlayerVisionHeight();
}

std::vector<int> ClientWorldMonitor::getPositionLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getPositionLookingAt());
}


std::vector<int> ClientWorldMonitor::getPriestLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getPriestLookingAt());
}


std::vector<int> ClientWorldMonitor::getNpcLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getNpcLookingAt());
}

std::vector<int> ClientWorldMonitor::getItemStandingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getItemStandingAt());
}

std::vector<int> ClientWorldMonitor::getGoldStandingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getGoldStandingAt());
}

client_world_t ClientWorldMonitor::getCurrentWorld() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(map.getCurrentWorld());
}

std::vector<int> ClientWorldMonitor::getDimensions(){
    return std::move(map.getDimensions());
}



void ClientWorldMonitor::interact() {
    std::unique_lock<std::mutex> lk(m);
    map.interact();
}
void ClientWorldMonitor::uninteract() {
    std::unique_lock<std::mutex> lk(m);
    map.uninteract();
}

int ClientWorldMonitor::isInteracting() {
    std::unique_lock<std::mutex> lk(m);
    return map.isInteracting();
}
