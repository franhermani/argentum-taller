#include "world.h"

World::World(GameParams& params) : params(params) {
    loadMatrix();
}

void World::loadMatrix() {
    json matrix_params = params.getWorldParams()["layers"][0];
    width = matrix_params["width"],
    height = matrix_params["height"];
    auto terrains = matrix_params["data"];

    matrix.resize(height);
    int i, j;
    for (i = 0; i < height; i ++) {
        std::vector<Terrain> row;
        row.resize(width);
        matrix.push_back(row);
        for (j = 0; j < width; j ++) {
            int pos = (width * i) + j;
            int terrain_type = terrains[pos];
            auto terrain = static_cast<Terrain>(terrain_type);
            matrix[i].push_back(terrain);
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
