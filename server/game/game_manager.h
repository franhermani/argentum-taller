#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include "../../common/thread.h"
#include "../utilities/json_parser.h"
#include "params.h"
#include "world.h"
#include "world_monitor.h"
#include "../../common/blocking_queue.h"
#include "id_manager.h"

class GameManager : public Thread {
    JsonParser jsonParser;
    GameParams* params;
    World* world;
    WorldMonitor* worldMonitor;
    BlockingQueue<Command*>* commandQueue;
    IdManager idManager;

public:
    // Constructor
    explicit GameManager(File& config_file);

    // Constructor y asignacion por copia deshabilitados
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager& other) = delete;

    // Destructor
    // Libera la memoria reservada para 'params', 'world' y para cada player
    ~GameManager();

    // Game loop
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;

    // Agrega y devuelve el ID asociado al 'username' recibido
    // Agrega el ID al idManager
    const int addIdByUsername(const std::string& username);

    // Agrega 'player' a 'world'
    void addPlayerToWorld(Player* player);

    // Elimina 'player' de 'world'
    void removePlayerFromWorld(const int id);

    // Devuelve un puntero a 'world' para que interactuen los players y npcs
    World* getWorld() const;

    // Devuelve un puntero a 'worldMonitor' para que interactuen los threads
    WorldMonitor* getWorldMonitor() const;

    // Devuelve una puntero a 'commandQueue'
    BlockingQueue<Command*>* getCommandQueue() const;
};

#endif // GAME_MANAGER_H
