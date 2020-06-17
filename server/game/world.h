#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include "params.h"
#include "player.h"
#include "../../common/defines/terrain.h"

class World {
    GameParams& params;
    std::vector<Player*> players;
    std::vector<std::vector<Terrain>> matrix;
    int world_width, world_height;
    int player_width, player_height;

    // Llena la matriz (mapa) segun el json generado por Tiled
    void loadMatrix();

    // Determina si una posicion (x,y) esta dentro de los limites de 'player'
    bool inPlayerBoundaries(Player& player, int pos_x, int pos_y);

public:
    // Constructor
    explicit World(GameParams& params);

    // Constructor y asignacion por copia deshabilitados
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    // --------------------------------------------- //
    // Metodos accedidos por WorldMonitor unicamente //
    // --------------------------------------------- //

    // Actualiza el mundo segun los milisegundos recibidos
    // Simula el paso del tiempo llamando al metodo update()
    // de todos los players y npcs
    void update(int ms);

    // Agrega un Player al mundo
    void addPlayer(Player* player);

    // Remueve un Player del mundo segun su ID
    void removePlayer(const int id);

    // Devuelve una sub-matriz del mapa segun la posicion del Player recibido
    std::vector<std::vector<Terrain>> getMatrixAround(Player& player);

    // Devuelve un vector de todos los players en la sub-matriz de 'player'
    // Incluye al mismo 'player' recibido por parametro
    std::vector<Player*> getPlayersAround(Player& player);

    // Devuelve un vector de todos los npc en la sub-matriz de 'player'
//    std::vector<NPC*> getNPCsAround(Player& player);

    // Devuelve un vector de todos los items en la sub-matriz de 'player'
//    std::vector<Item*> getItemsAround(Player& player);


    // --------------------------------------------- //
    // Metodos accedidos por Player y NPC unicamente //
    // --------------------------------------------- //

    // Determina si la posicion (x,y) esta dentro de los limites del mapa
    bool inMapBoundaries(int pos_x, int pos_y);

    // Determina si hay algun GameObject impenetrable en la posicion (x,y)
    bool inCollision(int pos_x, int pos_y);

    // Devuelve la base del mapa
    const int getWidth() const;

    // Devuelve la altura del mapa
    const int getHeight() const;
};

#endif // GAME_WORLD_H
