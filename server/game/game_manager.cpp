#include <string>
#include <thread>
#include <chrono>
#include "game_manager.h"
#include "game_exception.h"

GameManager::GameManager(File& config_file) :
worldFile(jsonParser.getConfigParams(config_file)["world_path"]),
params(jsonParser.getConfigParams(config_file),
        jsonParser.getWorldParams(worldFile)),
equations(params.getConfigParams()),
world(params),
worldMonitor(world),
msPerSend(params.getConfigParams()["ms_per_send"]) {
    keepRunning = true;
    isRunning = true;
}

void GameManager::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    int ms_per_update = params.getConfigParams()["ms_per_update"];

    while (keepRunning) {
        auto start = clock::now();
        while (! commandQueue.isEmpty()) {
            try {
                Command* command = commandQueue.pop();
                try {
                    command->execute();
                } catch (GameException& e) {
                    // TODO: encolar e.errorCode en una estructura compartida
                    // para que luego el sender le envie al cliente el codigo
                    // de error y este le muestre un mensaje al usuario
                }
                delete command;
            } catch(ClosedQueueException&) {
                break;
            }
        }
        worldMonitor.update(ms_per_update);
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = ms_per_update - elapsed;
        if (time_to_sleep > 0) std::this_thread::sleep_for(ms(time_to_sleep));
    }
    isRunning = false;
}

void GameManager::stop() {
    commandQueue.close();
    keepRunning = false;
}

bool GameManager::isDead() {
    return (! isRunning);
}

const int GameManager::addIdByUsername(const std::string &username) {
    return idManager.addPlayerByUsername(username);
}

void GameManager::addPlayerToWorld(Player* player) {
    worldMonitor.addPlayer(player);
}

void GameManager::removePlayerFromWorld(const int id) {
    worldMonitor.removePlayer(id);
}

void GameManager::removeUsername(const std::string& username) {
    idManager.removeUsername(username);
}
