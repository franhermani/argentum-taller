#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include "player.h"
#include "world.h"
#include "params.h"
#include "../utilities/file_parser.h"

class GameManager {
    FileParser& fileParser;
    World world;
    std::vector<Player> players;
    GameParams params;

public:
    // Constructor
    explicit GameManager(FileParser& file_parser);

    // Constructor y asignacion por copia deshabilitados
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager& other) = delete;
};

#endif // GAME_MANAGER_H
