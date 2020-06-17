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
                // TODO: implementar BlockingQueue<Command*>
                // es la cola compartida entre GameManager y ClientReceiver
                // Cerrar la cola de algun lado para que no se cuelgue aca!!!
                Command* command = commandQueue.pop();
                command->execute(player);
                delete command;
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

const int GameManager::addIdByUsername(const std::string &username) {
    return idManager.addPlayerByUsername(username);
}

void GameManager::addPlayerToWorld(Player* player) {
    world->addPlayer(player);
}

void GameManager::removePlayerFromWorld(const int id) {
    world->removePlayer(id);
}

World* GameManager::getWorld() const {
    return world;
}
