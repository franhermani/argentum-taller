

#include "map_monitor.h"

MapMonitor::MapMonitor() {}

MapMonitor::~MapMonitor() {}

//inicializa matriz
void MapMonitor::initializeMatrix(matrix_t receivedMatrix) {
    std::unique_lock<std::mutex> lk(m);
    //TODO CUIDADO COPIAS CAMBIAR
    map.initializeMatrix(receivedMatrix);
}

//actualiza el vector de jugadores y manda a renderizar
void MapMonitor::updateWorld(world_t receivedWorld) {
    std::unique_lock<std::mutex> lk(m);
    //TODO CUIDADO COPIAS CAMBIAR
    map.updateWorld(receivedWorld);
}
