
#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H
#include "../../common/defines/world_structs.h"
#include <vector>

class Map {
    world_t world;
    matrix_t matrix;
    //TODO SETEAR ESTOS recibidos al principio
    int playerVisionWidth;
    int playerVisionHeight;
public:
    // constructor
    Map();
    // destructor
    ~Map();

    //inicializa matriz
    void initializeMatrix(matrix_t receivedMatrix);

    //actualiza el vector de jugadores y manda a renderizar
    void updateWorld(world_t receivedWorld);

    std::vector<std::vector<Terrain>> getTerrains();

    std::vector<player_t> getRenderablePlayers();
};


#endif //ARGENTUM_MAP_H
