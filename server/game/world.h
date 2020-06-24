#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include <set>
#include "params.h"
#include "player.h"
#include "../../common/defines/terrains.h"

class World {
    GameParams& params;
    std::vector<std::vector<Terrain>> matrix;
    std::set<Terrain> impenetrableTerrains;
    std::vector<Player*> players;
    std::vector<Item*> items;
    int worldWidth, worldHeight;
    int playerWidth, playerHeight;

    // Llena el vector de terrenos impenetrables
    void loadImpenetrableTerrains();

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

    // Devuelve los bloques de vision del player (en ancho)
    const int getPlayerWidth();

    // Devuelve los bloques de vision del player (en alto)
    const int getPlayerHeight();

    // Devuelve la matriz del mapa completo
    std::vector<std::vector<Terrain>> getMatrix() const;

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

    // Determina si hay algun Player o NPC en la posicion (x,y)
    bool inCollision(int pos_x, int pos_y);

    // Agrega un item al mundo
    void addItem(Item* item);

    // Remueve un item del mundo segun su pos (x,y)
    Item* removeItem(int pos_x, int pos_y);

    Player* getPlayerById(const int id) const;

    const int getInventoryLength() const;


    // ------------------------------------------------ //
    // Metodos accedidos por WorldMonitor, Player y NPC //
    // ------------------------------------------------ //

    // Devuelve la base del mapa
    const int getWidth() const;

    // Devuelve la altura del mapa
    const int getHeight() const;
};

#endif // GAME_WORLD_H
