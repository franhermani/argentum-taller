#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include "../../common/thread.h"
#include "../utilities/json_parser.h"
#include "params.h"
#include "world.h"
#include "id_manager.h"
#include "../../common/blocking_queue.h"
#include "../../common/user_event.h"

class GameManager : public Thread {
    JsonParser jsonParser;
    GameParams* params;
    World* world;
    IdManager idManager;
    BlockingQueue<UserEvent> usersEvents;

public:
    // Constructor
    explicit GameManager(File& config_file);

    // Constructor y asignacion por copia deshabilitados
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager& other) = delete;

    // Destructor
    // Libera la memoria reservada para 'params' y 'world'
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
