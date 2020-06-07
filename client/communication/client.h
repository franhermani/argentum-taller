#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "../../common/socket.h"

class Client {
    Socket socket;
    bool keepPlaying;

public:
    // Constructor
    // Asocia al cliente al 'host' y 'port' recibidos por consola
    Client(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    // Comienza el juego
    void play();
};

#endif // CLIENT_H
