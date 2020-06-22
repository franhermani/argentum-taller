#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <SDL2/SDL_image.h>
#include "game/game_handler.h"

class Client {
    GameHandler* gameHandler;

public:
    // Constructor
    // Asocia al cliente al 'host' y 'port' recibidos
    Client(const char *host, const char *port, const std::string& username,
            const uint8_t race_type, const uint8_t class_type);

    // Constructor y asignacion por copia deshabilitados
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    // Destructor
    // Libera la memoria reservada para el connection handler
    ~Client();

    // Conecta al cliente con el servidor
    void connectToServer();

    // Desconecta al cliente del servidor
    void disconnectFromServer();

};

#endif // CLIENT_H
