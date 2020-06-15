#include <string>
#include <thread>
#include <chrono>
#include "game_manager.h"
#include "player.h"

GameManager::GameManager(File& config_file) {
    File world_file("../server/config/world.json");
    params = new GameParams(jsonParser.getConfigParams(config_file),
                            jsonParser.getWorldParams(world_file));
    world = new World(*params);
    keepRunning = true;
    isRunning = true;
}

GameManager::~GameManager() {
    for (auto player : players) delete player;
    delete world;
    delete params;
}

void GameManager::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    int ms_per_update = params->getConfigParams()["ms_per_update"];

    while (keepRunning) {
        auto start = clock::now();

        /*
        while (true) {
            try {
                UserEvent user_event = usersEvents.pop();
                handleEvent(user_event);
                world->update(ms_per_update);
            } catch(ClosedQueueException&) {
                break;
            }
        }
         */
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = ms_per_update - elapsed;
        if (time_to_sleep > 0) std::this_thread::sleep_for(ms(time_to_sleep));
    }
    isRunning = false;
}

void GameManager::stop() {
    keepRunning = false;
}

bool GameManager::isDead() {
    return (! isRunning);
}

void GameManager::addPlayer(const std::string &username) {
    int id = idManager.addPlayerByUsername(username);
    auto *player = new Player(*world, id);
    players.push_back(player);
    world->addPlayer(player);
}

void GameManager::removePlayer(const std::string &username) {
    int id = idManager.getPlayerId(username);
    size_t i;
    for (i = 0; i < players.size(); i ++) {
        if (players[i]->id == id) {
            world->removePlayer(id);
            players.erase(players.begin() + i);
            delete players[i];
        }
    }
}

void GameManager::handleEvent(UserEvent &user_event) {
    // TODO: estos eventos modifican efectivamente los GameObjects
}

World* GameManager::getWorld() const {
    return world;
}
