
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
    std::cout << "\n\n esta es la received height y width " << matrix.height << matrix.width;
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
    int x_start, y_start, x_finish, y_finish;

    x_start = x_player - playerVisionWidth/2;
    if (x_start < 0) x_start = 0;
    y_start = y_player - playerVisionHeight/2;
    if (y_start < 0) y_start = 0;

    //TODO ojo con este +1 que es porque 9/2 da 4 y sino me morfo un pedazo
    x_finish = x_player + (playerVisionWidth / 2) +1;
    if (x_finish >= matrix.width) x_finish = matrix.width;
    y_finish = y_player + (playerVisionHeight / 2 ) +1;
    if (y_finish >= matrix.height) y_finish = matrix.height;

    std::cout << "\n\nel player va a ver en x desde "<<x_start << " hasta " << x_finish
    << " y va a ver y desde "<<y_start << " hasta "<<y_finish<< "\n\n" << matrix.width;


    int current_column_index = 0;
    for (int i=x_start; i<x_finish; i++) {
        std::vector<Terrain> row;
        row.resize(playerVisionWidth);
        int current_row_index = 0;
        for (int j = y_start; j < y_finish; j++) {
            row[current_row_index] = received_terrain[i][j];
            ++current_row_index;
        }
        sub_matrix[current_column_index] = row;
        ++current_column_index;
    }

        /*


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
    }*/
    std::cout << "\n\n\n\n\nahora te meto esto 6 \n\n\n\n "<<sub_matrix[3][2];


    std::cout << "\n\n\n\n\n\np player pos x " << x_player << " -- player pos y "<<y_player << "\n";
    std::cout << "\n estoy devolviendo para renderizar una matriz de "<< sub_matrix.size() << " por  " <<sub_matrix[0].size();
    std::cout << "\n\nel player va a ver en x desde "<<x_start << " hasta " << x_finish
              << " y va a ver y desde "<<y_start << " hasta "<<y_finish<< "  de la matriz original que es de " << matrix.width
              << " por " <<matrix.height;
    return sub_matrix;

}


std::vector<player_t> Map::getRenderablePlayers() {
    player_t main_player;
    for (int i=0; i<world.num_players; i++) {
        if (username_id == world.players[i].id) {
            main_player = world.players[i];
        }
    }

    //copiamos
    std::vector<player_t> visible_players;
    int x_start, y_start, x_finish, y_finish;
    x_start = main_player.pos_x - playerVisionWidth/2;
    if (x_start < 0) x_start = 0;
    y_start = main_player.pos_y - playerVisionHeight/2;
    if (y_start < 0) y_start = 0;
    x_finish = main_player.pos_x  + (playerVisionWidth / 2);
    if (x_finish >= matrix.width) x_finish = matrix.width;
    y_finish = main_player.pos_y  + (playerVisionHeight / 2 );
    if (y_finish >= matrix.height) y_finish = matrix.height;



    //traducimos posiciones a la vision del jugador
    for(auto& player: world.players) {
        if ((player.pos_x < x_start) ||  (player.pos_x > x_finish) || (player.pos_y < y_start) || (player.pos_y > y_finish)) {
            continue;
        } else {
            player_t converted_player = player;
            converted_player.pos_x = player.pos_x - x_start;
            if (converted_player.pos_x < 0) converted_player.pos_x = 0;
            converted_player.pos_y = player.pos_y - y_start;
            if (converted_player.pos_y < 0) converted_player.pos_y = 0;
            visible_players.push_back(converted_player);
            std::cout << "\n hice traduccion de posicion x "<< player.pos_x;
            std::cout << " a la posicion " << converted_player.pos_x;
            std::cout << "\n hice traduccion de posicion y "<< player.pos_y;
            std::cout << " a la posicion " << converted_player.pos_y;
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