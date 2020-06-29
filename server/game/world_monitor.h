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

    // Devuelve la matriz del mapa completo
    std::vector<std::vector<Terrain>> getMatrix();

    // Devuelve la base del mapa
    const int getWidth();

    // Devuelve la altura del mapa
    const int getHeight();

    // Devuelve los bloques de vision del player (en ancho)
    const int getPlayerWidth();

    // Devuelve los bloques de vision del player (en alto)
    const int getPlayerHeight();

    // Devuelve un vector de todos los players en la sub-matriz de 'player'
    // Incluye al mismo 'player' recibido por parametro
    std::vector<Player*> getPlayersAround(Player& player);

    // Devuelve un vector de todas las criaturas en la sub-matriz de 'player'
    std::vector<Creature*> getCreaturesAround(Player& player);

    // Devuelve un vector de todos los items en la sub-matriz de 'player'
    std::vector<Item*> getItemsAround(Player& player);
};

#endif // WORLD_MONITOR_H
