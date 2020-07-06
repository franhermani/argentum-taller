
#ifndef ARGENTUM_MAP_MONITOR_H
#define ARGENTUM_MAP_MONITOR_H
#include <vector>
#include "map.h"
#include <mutex>



class MapMonitor {
    std::mutex m;
    Map map;

public:
    // Constructor
    MapMonitor();

    // Destructor
    ~MapMonitor();

    // Constructor y asignacion por copia deshabilitados
    MapMonitor(const MapMonitor& other) = delete;
    MapMonitor& operator=(const MapMonitor& other) = delete;

    //inicializa matriz
    void initialize(int username_id, std::vector<int>& blocks_around,
            matrix_t& received_matrix, npcs_t& npcs);

    //actualiza el vector de jugadores
    void updateWorld(world_t receivedWorld);

    //todo fix devolver referencia
    std::vector<std::vector<Terrain>> getTerrains();

    //todo fix devolver referencia
    std::vector<player_t> getRenderablePlayers();

    //fix devolver referencia
    std::vector<creature_t> getRenderableCreatures();

    std::vector<item_t> getRenderableItems();

    //todo fix devolver referencia
    std::vector<npc_t> getRenderableNpcs();

    int getPlayerVisionWidth();
    int getPlayerVisionHeight();

    // devuelve la posicion mas cercana apuntando
    // a la orientacion del jugador principal
    std::vector<int> getPositionLookingAt();

    std::vector<int> getPriestLookingAt();

    std::vector<int> getItemLookingAt();

    std::vector<int> getNpcLookingAt();

    player_info_t getPlayerInfo();

    player_t getMainPlayer();

    client_world_t getCurrentWorld();
    };


#endif //ARGENTUM_MAP_MONITOR_H
