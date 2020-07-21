
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
    world.initialize(username_id, blocks_around, npcs, map_dimensions);
}

void ClientWorldMonitor::updateWorld(world_t receivedWorld, list_t list) {
    std::unique_lock<std::mutex> lk(m);
    world.updateWorld(std::move(receivedWorld), std::move(list));
}

int ClientWorldMonitor::getPlayerVisionWidth() {
    return world.getPlayerVisionWidth();
}


int ClientWorldMonitor::getPlayerVisionHeight() {
    return world.getPlayerVisionHeight();
}

std::vector<int> ClientWorldMonitor::getPositionLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(world.getPositionLookingAt());
}


std::vector<int> ClientWorldMonitor::getPriestLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(world.getPriestLookingAt());
}


std::vector<int> ClientWorldMonitor::getNpcLookingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(world.getNpcLookingAt());
}

std::vector<int> ClientWorldMonitor::getItemStandingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(world.getItemStandingAt());
}

std::vector<int> ClientWorldMonitor::getGoldStandingAt() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(world.getGoldStandingAt());
}

client_world_t ClientWorldMonitor::getCurrentWorld() {
    std::unique_lock<std::mutex> lk(m);
    return std::move(world.getCurrentWorld());
}

std::vector<int> ClientWorldMonitor::getDimensions(){
    return std::move(world.getDimensions());
}



void ClientWorldMonitor::interact() {
    std::unique_lock<std::mutex> lk(m);
    world.interact();
}
void ClientWorldMonitor::uninteract() {
    std::unique_lock<std::mutex> lk(m);
    world.uninteract();
}

int ClientWorldMonitor::isInteracting() {
    std::unique_lock<std::mutex> lk(m);
    return world.isInteracting();
}
