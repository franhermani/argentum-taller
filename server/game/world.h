#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <mutex>
#include <vector>
#include "params.h"
#include "player.h"
#include "../../common/terrain.h"

class World {
    std::mutex m;
    GameParams& params;
    std::vector<Player*> players;
    std::vector<std::vector<Terrain>> matrix;
    int width{}, height{};

    // Llena la matriz (mapa) segun el json generado por Tiled
    void loadMatrix();

public:
    // Constructor
    explicit World(GameParams& params);

    // Constructor y asignacion por copia deshabilitados
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    // Agrega un Player al mundo
    void addPlayer(Player* player);

    // Remueve un Player del mundo segun su ID
    void removePlayer(const int id);

    // Determina si la posicion (x,y) esta dentro de los limites del mapa
    bool inMapBoundaries(int pos_x, int pos_y);

    // Determina si hay algun GameObject impenetrable en la posicion (x,y)
    bool inCollision(int pos_x, int pos_y);

    // Actualiza el mundo segun los milisegundos recibidos
    // Simula el paso del tiempo llamando al metodo update()
    // de todos los objetos dentro de 'gameObjects'
    void update(int ms);

    // Devuelve la base del mapa
    const int getWidth() const;

    // Devuelve la altura del mapa
    const int getHeight() const;

    // Devuelve una sub-matriz del mapa segun la posicion del Player recibido
    std::vector<std::vector<Terrain>> getSubMatrix(Player& player);
};

#endif // GAME_WORLD_H
