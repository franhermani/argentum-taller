#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include "../../common/thread.h"
#include "../utilities/file_parser.h"
#include "world.h"
#include "params.h"

class GameManager : public Thread {
    FileParser& fileParser;
    World* world;
    GameParams params;

public:
    // Constructor
    explicit GameManager(FileParser& file_parser);

    // Constructor y asignacion por copia deshabilitados
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager& other) = delete;

    // Destructor
    // Libera la memoria reservada para el world
    ~GameManager();

    // Game loop
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // GAME_MANAGER_H
