#include "manager.h"

GameManager::GameManager(FileParser& file_parser) : fileParser(file_parser),
params(fileParser.getGameParams()) {
    keepRunning = true;
    isRunning = true;
}

void GameManager::run() {
    while (keepRunning) {
        // TODO: ...
    }
    isRunning = false;
}

void GameManager::stop() {
    keepRunning = false;
}

bool GameManager::isDead() {
    return (! isRunning);
}
