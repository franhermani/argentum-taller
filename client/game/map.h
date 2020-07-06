
#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H
#include "../../common/defines/world_structs.h"
#include "map_structs.h"
#include <vector>

class Map {
    world_t world;
    matrix_t matrix;
    npcs_t npcs;

    int username_id;
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
    void initialize(int username_id, std::vector<int>
            blocks_around, matrix_t received_terrains, npcs_t npcs);

    //actualiza el vector de jugadores
    void updateWorld(world_t receivedWorld);

    // devuelve la posicion mas cercana apuntando
    // a la orientacion del jugador principal
    std::vector<int> getPositionLookingAt();

    std::vector<int> getPositionStandingAt();

    std::vector<int> getPriestLookingAt();

    std::vector<int> getNpcLookingAt();

    std::vector<int> getItemStandingAt();

    // devuelve la matriz de pisos
    std::vector<std::vector<Terrain>> getTerrains();

    // devuelve los jugadores dentro del rango de vision del jguador principal
    // con posiciones actualizadas a la submatriz
    std::vector<player_t> getRenderablePlayers();

    // devuelve los npcs dentro del rango de vision del jguador principal
    // con posiciones actualizadas a la submatriz
    std::vector<npc_t> getRenderableNpcs();

    std::vector<creature_t> getRenderableCreatures();

    std::vector<item_t> getRenderableItems();
        //
    int getPlayerVisionWidth();

    int getPlayerVisionHeight();

    //busca en la lista actual de jugadores y devuelve el principal
    player_t getMainPlayer();

    //imprime la matriz recibida de terrains por consola para debugeo
    void printDebugTerrainMatrix(std::vector<
            std::vector<Terrain>>& received_matrix);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // arrancaria en X su submatriz dentro de la matriz principal
    int getPlayerXStart(player_t& player);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // arrancaria en Y su submatriz dentro de la matriz principal
    int getPlayerYStart(player_t& player);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // terminaria en X su submatriz dentro de la matriz principal
    int getPlayerXEnd(player_t& player);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // terminaria en Y su submatriz dentro de la matriz principal
    int getPlayerYEnd(player_t& player);

    player_info_t getPlayerInfo();

    client_world_t getCurrentWorld();
};




#endif //ARGENTUM_MAP_H
