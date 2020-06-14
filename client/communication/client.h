#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "connection_handler.h"

#include <SDL2/SDL_image.h>


enum Terrain {
    TERRAIN_GRASS,
    TERRAIN_LAND,
    TERRAIN_SAND,
    TERRAIN_STONE,
    TERRAIN_WALL,
    TERRAIN_WATER,
};
enum Warrior {
    WARRIOR_UP,
    WARRIOR_DOWN,
    WARRIOR_RIGHT,
    WARRIOR_LEFT
};
enum Skeleton {
    SKELETON_UP,
    SKELETON_DOWN,
    SKELETON_RIGHT,
    SKELETON_LEFT
};

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

    // Destructor
    // Libera la memoria reservada para el connection handler
    ~Client();

    // Conecta al cliente con el servidor
    void connectToServer();

    // Desconecta al cliente del servidor
    void disconnectFromServer();

    // Comienza el juego
    void play();

    void render_map();

    void render_terrain(SDL_Surface* ScreenSurface, std::vector<std::vector<Terrain>> matrix);
};

#endif // CLIENT_H
