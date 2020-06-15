#include "world.h"

World::World(GameParams& params) : params(params) {
    loadMatrix();
}

void World::loadMatrix() {
    json js = params.getWorldParams()["layers"][0];
    width = js["width"],
    height = js["height"];
    auto terrains = js["data"];

    matrix.resize(height);
    int i, j, pos, terrain_type;
    for (i = 0; i < height; i ++) {
        std::vector<Terrain> row;
        row.resize(width);
        matrix.push_back(row);
        for (j = 0; j < width; j ++) {
            pos = (width * i) + j;
            terrain_type = terrains[pos];
            matrix[i].push_back(static_cast<Terrain>(terrain_type));
        }
    }
}

void World::addPlayer(Player* player) {
    std::unique_lock<std::mutex> lk(m);
    players.push_back(player);
}

void World::removePlayer(int id) {
    std::unique_lock<std::mutex> lk(m);
    size_t i;
    for (i = 0; i < players.size(); i ++)
        if (players[i]->id == id)
            players.erase(players.begin() + i);
}

bool World::inMapBoundaries(int pos_x, int pos_y) {
    std::unique_lock<std::mutex> lk(m);
    bool x_in_boundaries = (pos_x >= 0) && (pos_x < width),
         y_in_boundaries = (pos_y >= 0) && (pos_y < height);

    return x_in_boundaries && y_in_boundaries;
}

bool World::inCollision(int pos_x, int pos_y) {
    std::unique_lock<std::mutex> lk(m);
    for (auto player : players)
        if (player->posX == pos_x && player->posY == pos_y)
            return true;
    return false;
}

void World::update(int ms) {
    std::unique_lock<std::mutex> lk(m);
    for (auto player : players) player->update(ms);
}

const int World::getWidth() const {
    return width;
}

const int World::getHeight() const {
    return height;
}

std::vector<std::vector<Terrain>> World::getSubMatrix(Player &player) {
    std::unique_lock<std::mutex> lk(m);
    std::vector<std::vector<Terrain>> sub_matrix;
    json js = params.getConfigParams()["blocks_around_player"];
    int s_width = js["width"], s_height = js["height"];
    int x_player = player.posX, y_player = player.posY;

    sub_matrix.resize(s_height);
    int i, j, pos_x, pos_y;
    for (i = 0; i < s_height; i ++) {
        std::vector<Terrain> row;
        row.resize(s_width);
        sub_matrix.push_back(row);
        for (j = 0; j < s_width; j ++) {
            pos_x = x_player - s_width/2 + j;
            pos_y = y_player - s_height/2 + i;
            if (! inMapBoundaries(pos_x, pos_y)) {
                sub_matrix[i].push_back(TERRAIN_OUT_OF_BOUNDARIES);
            } else {
                sub_matrix[i].push_back(matrix[pos_y][pos_x]);
            }
        }
    }
    return sub_matrix;
}
