#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <mutex>
#include <vector>
#include "params.h"
#include "game_object.h"
#include "../../common/terrain.h"

#define WIDTH 100
#define HEIGHT 100

class World {
    std::mutex m;
    GameParams& params;
    // TODO: ver si es puntero o no
    std::vector<GameObject*> gameObjects;
    // TODO: tomar estos valores del json
    Terrain matrix[WIDTH][HEIGHT]{};

    // Llena la matriz (mapa) segun el json generado por Tiled
    void loadMatrix();

public:
    // Constructor
    explicit World(GameParams& params);

    // Constructor y asignacion por copia deshabilitados
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    // Agrega un GameObject al mundo
    // TODO: ver si es puntero o no
    void addGameObject(GameObject* game_object);

    // Remueve un GameObject del mundo segun su ID
    void removeGameObject(int id);

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
};

#endif // GAME_WORLD_H
