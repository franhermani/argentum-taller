#include <string>
#include <thread>
#include <chrono>
#include "game_manager.h"

GameManager::GameManager(File& config_file) {
    File world_file(jsonParser.getConfigParams(config_file)["world_path"]);

    params = new GameParams(jsonParser.getConfigParams(config_file),
                            jsonParser.getWorldParams(world_file));

    equations = new Equations(params->getConfigParams());
    world = new World(*params);
    worldMonitor = new WorldMonitor(*world);
    commandQueue = new BlockingQueue<Command*>();

    msPerSend = params->getConfigParams()["ms_per_send"];

    keepRunning = true;
    isRunning = true;
}

GameManager::~GameManager() {
    delete commandQueue;
    delete worldMonitor;
    delete world;
    delete equations;
    delete params;
}

void GameManager::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    int ms_per_update = params->getConfigParams()["ms_per_update"];

    while (keepRunning) {
        auto start = clock::now();
        while (! commandQueue->isEmpty()) {
            try {
                Command* command = commandQueue->pop();
                command->execute();
                delete command;
            } catch(ClosedQueueException&) {
                break;
            }
        }
        worldMonitor->update(ms_per_update);
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = ms_per_update - elapsed;
        if (time_to_sleep > 0) std::this_thread::sleep_for(ms(time_to_sleep));
    }
    isRunning = false;
}

void GameManager::stop() {
    commandQueue->close();
    keepRunning = false;
}

bool GameManager::isDead() {
    return (! isRunning);
}

const int GameManager::addIdByUsername(const std::string &username) {
    return idManager.addPlayerByUsername(username);
}

void GameManager::addPlayerToWorld(Player* player) {
    worldMonitor->addPlayer(player);
}

void GameManager::removePlayerFromWorld(const int id) {
    worldMonitor->removePlayer(id);
}
