#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "../common/utilities/json_parser.h"
#include "../common/utilities/file.h"
#include "game/game_manager.h"
#include "communication/clients_acceptor.h"

class Server {
    std::string port;
    JsonParser jsonParser;
    GameManager* gameManager;
    ClientsAcceptor* clientsAcceptor{};

public:
    // Constructor
    explicit Server(File& file);

    // Constructor y asignacion por copia deshabilitados
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    // Destructor
    ~Server();

    // Inicializa el game manager y el aceptador de clientes
    void startGame();

    // Finaliza el game manager y el aceptador de clientes
    void endGame();
};

#endif // SERVER_H
