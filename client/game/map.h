
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

    int betweenPlayerBorders(int pos_x, int pos_y);


    //busca en la lista actual de jugadores y devuelve el principal
    player_t getMainPlayer();

    //convierte un vector de terrains a matriz
    void initializeMatrixFromVector(matrix_t& received_matrix);



    int getNewBordersXPosition(int pos_x, player_t& main_player);
    int getNewBordersYPosition(int pos_y, player_t& main_player);



public:
    // constructor
    Map();
    // destructor
    ~Map();

    // Constructor y asignacion por copia deshabilitados
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    //inicializa matriz
    void initialize(int username_id, std::vector<int>&
            blocks_around, matrix_t& received_terrains, npcs_t& npcs);

    //actualiza el vector de jugadores recibido del server
    void updateWorld(world_t receivedWorld);

    // devuelve npc/posicion al que se mira
    std::vector<int> getPositionLookingAt();
    std::vector<int> getPriestLookingAt();
    std::vector<int> getNpcLookingAt();

    //devuelve item/posicion donde se esta prado
    std::vector<int> getPositionStandingAt();
    std::vector<int> getItemStandingAt();

    // devuelve la matriz de pisos
    std::vector<std::vector<Terrain>> getTerrains();


    // devuelve los npcs/players/criatura/item
    // dentro del rango de vision del jguador principal
    // con posiciones actualizadas a la submatriz
    std::vector<player_t> getRenderablePlayers();
    std::vector<npc_t> getRenderableNpcs();
    std::vector<creature_t> getRenderableCreatures();
    std::vector<item_t> getRenderableItems();
    std::vector<gold_t> getRenderableGolds();

    // getters de campo de vision del jugador
    int getPlayerVisionWidth();
    int getPlayerVisionHeight();

    //imprime por consola la matriz recibida de terrains para debugeo
    void printDebugTerrainMatrix(std::vector<
            std::vector<Terrain>>& received_matrix);

    //devuelve infomacion del estado actual del mundo
    client_world_t getCurrentWorld();
    };




#endif //ARGENTUM_MAP_H
