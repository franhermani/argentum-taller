#include <vector>
#include "world_monitor.h"

WorldMonitor::WorldMonitor(World& world) : world(world) {}

void WorldMonitor::addPlayer(Player *player) {
    std::unique_lock<std::mutex> lk(m);
    world.addPlayer(player);
}

void WorldMonitor::removePlayer(const int id) {
    std::unique_lock<std::mutex> lk(m);
    world.removePlayer(id);
}

void WorldMonitor::update(int ms) {
    std::unique_lock<std::mutex> lk(m);
    world.update(ms);
}

std::vector<std::vector<Terrain>> WorldMonitor::getMatrix() {
    std::unique_lock<std::mutex> lk(m);
    return world.getMatrix();
}

const int WorldMonitor::getWidth() {
    std::unique_lock<std::mutex> lk(m);
    return world.getWidth();
}

const int WorldMonitor::getHeight() {
    std::unique_lock<std::mutex> lk(m);
    return world.getHeight();
}

std::vector<std::vector<Terrain>> WorldMonitor::getMatrixAround(
        Player &player) {
    std::unique_lock<std::mutex> lk(m);
    return world.getMatrixAround(player);
}

std::vector<Player*> WorldMonitor::getPlayersAround(Player &player) {
    std::unique_lock<std::mutex> lk(m);
    return world.getPlayersAround(player);
}
