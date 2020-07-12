#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "../../common/thread.h"
#include "../utilities/json_parser.h"
#include "../utilities/math_calculator.h"
#include "params.h"
#include "equations.h"
#include "world.h"
#include "world_monitor.h"
#include "../../common/protected_queue.h"
#include "id_manager.h"
#include "bank.h"

class ClientHandler;

class GameManager : public Thread {
    JsonParser jsonParser;
    Math math;
    File worldFile;
    GameParams params;
    ItemFactory itemFactory;
    Equations equations;
    World world;
    WorldMonitor worldMonitor;
    ProtectedQueue<Command*> commandQueue;
    std::map<int, ProtectedQueue<std::string>> messagesQueuePerPlayer;
    std::map<int, ProtectedQueue<list_t>> listsQueuePerPlayer;
    IdManager idManager;
    Bank bank;
    int msPerSend;

    friend class ClientHandler;

    // Crea NPCs en posiciones random dentro de una zona segura
    void spawnNPCs();

    // Crea criaturas en posiciones random fuera de una zona segura
    void spawnCreatures();

public:
    // Constructor
    explicit GameManager(File& config_file);

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

    // Agrega y devuelve el ID asociado al 'username' recibido
    // Agrega el ID al idManager
    const int addIdByUsername(const std::string& username);

    // Agrega 'player' a 'world'
    void addPlayerToWorld(Player* player);

    // Elimina 'player' de 'world'
    void removePlayerFromWorld(const int id);

    // Elimina 'username' del idManager
    void removeUsername(const std::string& username);
};

#endif // GAME_MANAGER_H
