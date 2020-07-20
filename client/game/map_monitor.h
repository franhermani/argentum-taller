
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
            npcs_t& npcs,
            std::vector<int>& map_dimensions);

    //actualiza el vector de jugadores
    void updateWorld(world_t receivedWorld, list_t list);

    int getPlayerVisionWidth();
    int getPlayerVisionHeight();
    std::vector<int> getDimensions();

    // devuelve npc/posicion al que se mira
    std::vector<int> getPositionLookingAt();
    std::vector<int> getPriestLookingAt();

    //devuelve item/posicion donde se esta prado
    std::vector<int> getItemStandingAt();
    std::vector<int> getGoldStandingAt();
    std::vector<int> getNpcLookingAt();

    //Devuelve estado actual del mundo
    client_world_t getCurrentWorld();

    //npc interaction related functions
    void interact();
    void uninteract();
    int isInteracting();
    };


#endif //ARGENTUM_MAP_MONITOR_H
