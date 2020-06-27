
#include "map.h"
#include <vector>
#include <iostream>
#include "exception.h"

// constructor
Map::Map() {
}
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

void Map::initialize(int received_id,
        std::vector<int> blocks_around, matrix_t received_matrix) {
    int current_index = 0;
    for (int i=0; i<received_matrix.height; i++) {
        std::vector<Terrain> row;
        terrainMatrix.push_back(row);
        for (int j = 0; j < received_matrix.width; ++j) {
            terrainMatrix[i].push_back(received_matrix.terrains[current_index]);
            ++current_index;
        }
    }
    terrainMatrixHeight = received_matrix.height;
    terrainMatrixWidth = received_matrix.width;
    playerVisionWidth = blocks_around[0];
    playerVisionHeight = blocks_around[1];
    username_id = received_id;
}

//TODO esto podria devolver una ref
//puede haber un error?
player_t Map::getMainPlayer() {
    for (int i=0; i<world.num_players; i++) {
        if (username_id == world.players[i].id) {
            return world.players[i];
        }
    }
    throw GameException("main player not found");
}
int Map::xPosToUser(int x) {
    if (x >= playerVisionWidth) return x-playerVisionWidth;
    return x;
}
int Map::yPosToUser(int y) {
    if (y >= playerVisionWidth) return y-playerVisionWidth;
    return y;
}

void Map::printDebugTerrainMatrix(
        std::vector<std::vector<Terrain>>& received_matrix){
    int col_size = received_matrix.size();
    int row_size = received_matrix[0].size();
    std::cout << "\n\n\n ASI QUEDO LA MATRIZ\n\n\n";
    for (int i=0; i<col_size; i++) {
        for (int j=0; j< row_size; j++) {
            std::cout << received_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}



std::vector<std::vector<Terrain>> Map::getTerrains() {
    printDebugTerrainMatrix(terrainMatrix);
    player_t player = getMainPlayer();

    std::vector<std::vector<Terrain>> sub_matrix;
    int x_player = player.pos_x;
    int y_player = player.pos_y;

    sub_matrix.resize(playerVisionHeight);
    int x_start, y_start, x_finish, y_finish;
    x_start = getPlayerXStart(player);
    y_start = getPlayerYStart(player);
    //TODO ojo con este +1 que es porque 9/2 da 4 y sino me morfo un pedazo
    x_finish = x_player + (playerVisionWidth / 2) +1;
    if (x_finish >= terrainMatrixWidth) x_finish = terrainMatrixWidth;
    y_finish = y_player + (playerVisionHeight / 2) +1;
    if (y_finish >= terrainMatrixHeight) y_finish = terrainMatrixHeight;


    int current_column_index = 0;
    for (int i=y_start; i<y_finish; i++) {
        std::vector<Terrain> row;
        row.resize(playerVisionWidth);
        int current_row_index = 0;
        for (int j = x_start; j < x_finish; j++) {
            row[current_row_index] = terrainMatrix[i][j];
            ++current_row_index;
        }
        sub_matrix[current_column_index] = row;
        ++current_column_index;
    }
    printDebugTerrainMatrix(sub_matrix);
    return sub_matrix;
}

int Map::getPlayerXStart(player_t& player) {
    int x_start = player.pos_x - playerVisionWidth/2;
    if (x_start < 0) return 0;
    return x_start;
}
int Map::getPlayerYStart(player_t& player) {
    int y_start = player.pos_y - playerVisionHeight/2;
    if (y_start < 0) return 0;
    return y_start;
}

int Map::getPlayerXEnd(player_t& player) {
    int x_finish = player.pos_x  + (playerVisionWidth / 2) + 1;
    if (x_finish >= terrainMatrixWidth) return terrainMatrixWidth;
    return x_finish;
}

int Map::getPlayerYEnd(player_t& player) {
    int y_finish = player.pos_y  + (playerVisionHeight / 2) + 1;
    if (y_finish >= terrainMatrixHeight) return terrainMatrixHeight;
    return y_finish;
}



std::vector<player_t> Map::getRenderablePlayers() {
    player_t main_player = getMainPlayer();

    //Pedimos los bordes de vision del jugador en
    // coordenadas de la matriz principal
    int x_start, y_start, x_finish, y_finish;
    x_start = getPlayerXStart(main_player);
    y_start = getPlayerYStart(main_player);
    x_finish = getPlayerXEnd(main_player);
    y_finish = getPlayerYEnd(main_player);
    std::vector<player_t> visible_players;


    //traducimos posiciones a la vision del jugador y
    // nos quedamos con los jugadores que esten
    //dentro del rango de vision del principal
    for (auto& player: world.players) {
        if ((player.pos_x < x_start) ||  (player.pos_x > x_finish)
        || (player.pos_y < y_start) || (player.pos_y > y_finish)) {
            continue;
        } else {
            player_t converted_player = player;
            converted_player.pos_x = player.pos_x - x_start;
            if (converted_player.pos_x < 0) converted_player.pos_x = 0;
            converted_player.pos_y = player.pos_y - y_start;
            if (converted_player.pos_y < 0) converted_player.pos_y = 0;
            visible_players.push_back(converted_player);
        }
    }
    return visible_players;
}

int Map::getPlayerVisionWidth() {
    return playerVisionWidth;
}
int Map::getPlayerVisionHeight() {
    return playerVisionHeight;
}
