
#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H
#include "../../common/defines/world_structs.h"


class Map {
    world_t world;
    matrix_t matrix;
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


};


#endif //ARGENTUM_MAP_H
