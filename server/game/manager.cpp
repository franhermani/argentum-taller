#include <thread>
#include <chrono>
#include "manager.h"

#define MS_PER_UPDATE 60

GameManager::GameManager(FileParser& file_parser) : fileParser(file_parser),
params(fileParser.getGameParams()) {
    keepRunning = true;
    isRunning = true;
}

void GameManager::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    while (keepRunning) {
        auto start = clock::now();

        // TODO:
        // - Saco un evento de la cola
        // - Llamo al handler del evento

        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = MS_PER_UPDATE - elapsed;
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
