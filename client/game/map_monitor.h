
#ifndef ARGENTUM_MAP_MONITOR_H
#define ARGENTUM_MAP_MONITOR_H
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
    void initializeMatrix(matrix_t receivedMatrix);

    //actualiza el vector de jugadores y manda a renderizar
    void updateWorld(world_t receivedWorld);

};


#endif //ARGENTUM_MAP_MONITOR_H
