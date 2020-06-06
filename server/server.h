#ifndef SERVER_H
#define SERVER_H

#include "file.h"
#include "thread_acceptor.h"

class Server {
    File& configFile;
    const char *port;
    ThreadAcceptor *threadAcceptor;

public:
    // Constructor
    explicit Server(File& file);

    // Constructor y asignacion por copia deshabilitados
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    // Destructor
    ~Server();

    // Lee y parsea el archivo de configuracion
    void parseConfigFile();

    // Crea el threadAcceptor
    void createThreadAcceptor();

    // Inicializa el threadAcceptor
    void startThreadAcceptor();

    // Finaliza la ejecucion del threadAcceptor
    void stopThreadAcceptor();

    // Espera a que finalice el threadAcceptor
    void joinThreadAcceptor();
};

#endif // SERVER_H
