
#include "map.h"
#include <vector>
#include <iostream>


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

void Map::initialize(int received_id, std::vector<int> blocks_around, matrix_t received_matrix) {
    matrix = received_matrix;
    playerVisionWidth = blocks_around[0];
    playerVisionHeight = blocks_around[1];
    username_id = received_id;
}

int Map::xPosToUser(int x) {
    if (x >= playerVisionWidth) return x-playerVisionWidth;
    return x;
}
int Map::yPosToUser(int y) {
    if (y >= playerVisionWidth) return y-playerVisionWidth;
    return y;
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

    //TODO TODO TOOD OTOD OTODOT OTOTODOTODTODOT refactor ya




    player_t player;
    for (int i=0; i<world.num_players; i++) {
        if (username_id == world.players[i].id) {
            player = world.players[i];
        }
    }
    std::cout << "\n\n\n\n\nahora te meto esto2 \n\n\n\n ";//<<sub_matrix[2][2];

    std::cout << "esto es lo que vale vision height " << playerVisionHeight << " y eso vale width "<<playerVisionWidth << "\n";
    std::vector<std::vector<Terrain>> sub_matrix;
    int x_player = player.pos_x;
    int y_player = player.pos_y;
    std::cout << "esto es lo que vale player pos x " << x_player << " y eso vale y player "<<y_player << "\n";
    std::cout<< "\n\n\n\n\n\n meto esto 3\n\n\n\n" ;
    sub_matrix.resize(playerVisionHeight);

    int i, j, pos_x, pos_y;
    for (i=0; i<playerVisionHeight; i++) {
        std::vector<Terrain> row;
        row.resize(playerVisionWidth);
        for (j=0; j<playerVisionWidth; j++) {
            pos_x = x_player - playerVisionWidth/2 + j;
            pos_y = y_player - playerVisionHeight/2 + i;
            std::cout << pos_y << "-- " << pos_x;
            std::cout<< "\n\n\n\n\n\n meto esto 4\n\n\n\n" ;
            row[j] = received_terrain[pos_y][pos_x];
            std::cout<< "\n\n\n\n\n\n meto esto 5edio\n\n\n\n";
        }
        sub_matrix[i] = row;
    }
    std::cout << "\n\n\n\n\nahora te meto esto 6 \n\n\n\n ";//<<sub_matrix[2][2];


    return sub_matrix;

}


std::vector<player_t> Map::getRenderablePlayers() {
    //copiamos
    std::vector<player_t> visible_players = world.players;
    //traducimos posiciones a la vision del jugador
    for(auto& player: visible_players) {
        player.pos_x = xPosToUser(player.pos_x);
        player.pos_y = yPosToUser(player.pos_y);
    }
    return visible_players;
}

int Map::getPlayerVisionWidth() {
    return playerVisionWidth;
}
int Map::getPlayerVisionHeight() {
    return playerVisionHeight;
}