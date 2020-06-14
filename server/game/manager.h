#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include "../../common/thread.h"
#include "../utilities/json_parser.h"
#include "world.h"
#include "params.h"
#include "../../common/blocking_queue.h"
#include "../../common/user_event.h"

class GameManager : public Thread {
    JsonParser& jsonParser;
    World* world;
    GameParams params;
    BlockingQueue<UserEvent> usersEvents;

public:
    // Constructor
    explicit GameManager(JsonParser& json_parser);

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

    // Handler de los eventos de los usuarios
    void handleEvent(UserEvent& user_event);
};

#endif // GAME_MANAGER_H