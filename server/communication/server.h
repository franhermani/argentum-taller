#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "../utilities/file_parser.h"
#include "../utilities/file.h"
#include "../game/manager.h"
#include "clients_acceptor.h"

class Server {
    std::string port;
    FileParser fileParser;
    GameManager gameManager;
    ClientsAcceptor* clientsAcceptor{};

public:
    // Constructor
    explicit Server(File& file);

    // Constructor y asignacion por copia deshabilitados
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    // Destructor
    ~Server();

    // Inicializa el thread aceptador
    void startClientsAcceptor();

    // Finaliza la ejecucion del thread aceptador
    void stopClientsAcceptor();

    // Espera a que finalice el thread aceptador
    void joinClientsAcceptor();
};

#endif // SERVER_H
