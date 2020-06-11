#include <thread>
#include <chrono>
#include "manager.h"

GameManager::GameManager(FileParser& file_parser) : fileParser(file_parser),
params(fileParser.getGameParams()) {
    world = new World(params);
    keepRunning = true;
    isRunning = true;
}

GameManager::~GameManager() {
    delete world;
}

void GameManager::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    int ms_per_update = fileParser.getGameParams()["ms_per_update"];

    while (keepRunning) {
        auto start = clock::now();

        while (true) {
            try {
                UserEvent user_event = usersEvents.pop();
                handleEvent(user_event);
                world->update(ms_per_update);
            } catch(ClosedQueueException&) {
                break;
            }
        }
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

void GameManager::handleEvent(UserEvent &user_event) {
    // TODO: ...
}
