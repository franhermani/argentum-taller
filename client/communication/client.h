#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "connection_handler.h"

class Client {
    ConnectionHandler* connectionHandler;
    bool keepPlaying;

public:
    // Constructor
    // Asocia al cliente al 'host' y 'port' recibidos
    Client(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    // Conecta al cliente con el servidor
    void connectToServer();

    // Comienza el juego
    void play();
};

#endif // CLIENT_H
