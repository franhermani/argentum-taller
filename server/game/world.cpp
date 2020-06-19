#include "world.h"

World::World(GameParams& params) : params(params) {
    json js;
    js = params.getWorldParams()["layers"][0];
    world_width = js["width"], world_height = js["height"];

    js = params.getConfigParams()["blocks_around_player"];
    player_width = js["width"], player_height = js["height"];

    loadMatrix();
}

void World::loadMatrix() {
    json js = params.getWorldParams()["layers"][0];
    auto terrains = js["data"];

    matrix.resize(world_height);
    int i, j, pos, terrain_type;
    for (i = 0; i < world_height; i ++) {
        std::vector<Terrain> row;
        row.resize(world_width);
        matrix.push_back(row);
        for (j = 0; j < world_width; j ++) {
            pos = (world_width * i) + j;
            terrain_type = terrains[pos];
            matrix[i].push_back(static_cast<Terrain>(terrain_type));
        }
    }
}

// --------------------------------------------- //
// Metodos accedidos por WorldMonitor unicamente //
// --------------------------------------------- //

void World::update(int ms) {
    for (auto player : players) player->update(ms);
}

void World::addPlayer(Player* player) {
    players.push_back(player);
}

void World::removePlayer(int id) {
    size_t i;
    for (i = 0; i < players.size(); i ++)
        if (players[i]->id == id)
            players.erase(players.begin() + i);
}

std::vector<std::vector<Terrain>> World::getMatrix() const {
    return matrix;
}

std::vector<std::vector<Terrain>> World::getMatrixAround(Player &player) {
    std::vector<std::vector<Terrain>> sub_matrix;
    int x_player = player.posX, y_player = player.posY;

    sub_matrix.resize(player_height);
    int i, j, pos_x, pos_y;
    for (i = 0; i < player_height; i ++) {
        std::vector<Terrain> row;
        row.resize(player_width);
        sub_matrix.push_back(row);
        for (j = 0; j < player_width; j ++) {
            pos_x = x_player - player_width/2 + j;
            pos_y = y_player - player_height/2 + i;
            if (! inMapBoundaries(pos_x, pos_y)) {
                sub_matrix[i].push_back(TERRAIN_OUT_OF_BOUNDARIES);
            } else {
                sub_matrix[i].push_back(matrix[pos_y][pos_x]);
            }
        }
    }
    return sub_matrix;
}

std::vector<Player*> World::getPlayersAround(Player &player) {
    std::vector<Player*> players_around;

    for (auto& p : players)
        if (inPlayerBoundaries(player, p->posX, p->posY))
            players_around.push_back(p);

    return players_around;
}

bool World::inPlayerBoundaries(Player &player, int pos_x, int pos_y) {
    int player_xi = player.posX - player_width/2,
        player_xf = player.posX + player_width/2,
        player_yi = player.posY - player_height/2,
        player_yf = player.posY + player_height/2;

    bool x_in_boundaries = (pos_x >= player_xi) && (pos_x < player_xf),
         y_in_boundaries = (pos_y >= player_yi) && (pos_y < player_yf);

    return x_in_boundaries && y_in_boundaries;
}

// --------------------------------------------- //
// Metodos accedidos por Player y NPC unicamente //
// --------------------------------------------- //

bool World::inMapBoundaries(int pos_x, int pos_y) {
    bool x_in_boundaries = (pos_x >= 0) && (pos_x < world_width),
         y_in_boundaries = (pos_y >= 0) && (pos_y < world_height);

    return x_in_boundaries && y_in_boundaries;
}

// TODO: chequear tambien la lista de NPCs cuando la agregue
bool World::inCollision(int pos_x, int pos_y) {
    for (auto player : players)
        if (player->posX == pos_x && player->posY == pos_y)
            return true;
    return false;
}

const int World::getWidth() const {
    return world_width;
}

const int World::getHeight() const {
    return world_height;
}
