
#include "map.h"


// constructor
Map::Map() {}
// destructor
Map::~Map() {}

//actualiza el vector de jugadores y manda a renderizar
void Map::updateWorld(world_t receivedWorld) {
    //actualizo players
    world.players = receivedWorld.players;
    world.num_players = receivedWorld.num_players;
    world.player_info = receivedWorld.player_info;
    //el resto falta recibirlo
}

void Map::initializeMatrix(matrix_t received_matrix) {
    matrix = received_matrix;
}


std::vector<std::vector<Terrain>> Map::getTerrains() {
    std::vector<std::vector<Terrain>> received_terrain;
    received_terrain.resize(matrix.height);
    int current_index = 0;
    for (int i=0; i<matrix.height; i++) {
        std::vector<Terrain> row;
        row.resize(matrix.width);
        received_terrain.push_back(row);
        for (int j = 0; j < matrix.width; ++j) {
            received_terrain[i].push_back(matrix.terrains[current_index]);
            ++current_index;
        }
    }
    return received_terrain;
}


std::vector<player_t> Map::getRenderablePlayers() {
    return world.players;
}