#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "../utilities/file_parser.h"
#include "../utilities/file.h"
#include "../game/manager.h"
#include "thread_acceptor.h"

class Server {
    std::string port;
    FileParser fileParser;
    GameManager gameManager;
    ThreadAcceptor* threadAcceptor{};

public:
    // Constructor
    explicit Server(File& file);

    // Constructor y asignacion por copia deshabilitados
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    // Destructor
    ~Server();

    // Inicializa el threadAcceptor
    void startThreadAcceptor();

    // Finaliza la ejecucion del threadAcceptor
    void stopThreadAcceptor();

    // Espera a que finalice el threadAcceptor
    void joinThreadAcceptor();
};

#endif // SERVER_H
