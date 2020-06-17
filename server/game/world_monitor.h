#ifndef WORLD_MONITOR_H
#define WORLD_MONITOR_H

#include <mutex>
#include <vector>
#include "world.h"

class WorldMonitor {
    std::mutex m;
    World& world;

public:
    // Constructor
    explicit WorldMonitor(World& world);

    // Constructor y asignacion por copia deshabilitados
    WorldMonitor(const WorldMonitor& other) = delete;
    WorldMonitor& operator=(const WorldMonitor& other) = delete;

    // Agrega un Player al mundo
    void addPlayer(Player* player);

    // Remueve un Player del mundo segun su ID
    void removePlayer(const int id);

    // Actualiza el mundo segun los milisegundos recibidos
    // Simula el paso del tiempo llamando al metodo update()
    // de todos los players y npcs
    void update(int ms);

    // Devuelve una sub-matriz del mapa segun la posicion del Player recibido
    std::vector<std::vector<Terrain>> getMatrixAround(Player& player);

    // Devuelve un vector de todos los players en la sub-matriz de 'player'
    // Incluye al mismo 'player' recibido por parametro
    std::vector<Player*> getPlayersAround(Player& player);

    // Devuelve un vector de todos los npc en la sub-matriz de 'player'
//    std::vector<NPC*> getNPCsAround(Player& player);

    // Devuelve un vector de todos los items en la sub-matriz de 'player'
//    std::vector<Item*> getItemsAround(Player& player);
};

#endif // WORLD_MONITOR_H
