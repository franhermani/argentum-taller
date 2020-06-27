
#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H
#include "../../common/defines/world_structs.h"
#include <vector>

class Map {
    world_t world;
    matrix_t matrix;
    int username_id;
    std::vector<int> blocks_around;
    std::vector<std::vector<Terrain>> terrainMatrix;
    int terrainMatrixHeight;
    int terrainMatrixWidth;
    //TODO SETEAR ESTOS recibidos al principio
    int playerVisionWidth;
    int playerVisionHeight;
    int xPosToUser(int x);
    int yPosToUser(int y);
public:
    // constructor
    Map();
    // destructor
    ~Map();

    //inicializa matriz
    void initialize(int username_id, std::vector<int> blocks_around, matrix_t received_terrains);

    //actualiza el vector de jugadores y manda a renderizar
    void updateWorld(world_t receivedWorld);


    //
    std::vector<std::vector<Terrain>> getTerrains();

    std::vector<player_t> getRenderablePlayers();

    int getPlayerVisionWidth();

    int getPlayerVisionHeight();

    //busca en la lista actual de jugadores y devuelve el principal
    player_t getMainPlayer();

    //imprime la matriz recibida de terrains por consola para debugeo
    void printDebugTerrainMatrix(std::vector<std::vector<Terrain>>& received_matrix);




    };


#endif //ARGENTUM_MAP_H
