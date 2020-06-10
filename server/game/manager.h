#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <atomic>
#include "../../common/thread.h"
#include "player.h"
#include "world.h"
#include "params.h"
#include "../utilities/file_parser.h"

class GameManager : public Thread {
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

    // Game loop
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // GAME_MANAGER_H
