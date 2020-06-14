#include "world.h"

World::World(GameParams& params) : params(params) {
    loadMatrix();
}

void World::loadMatrix() {
    json world_params = params.getWorldParams();
//    int width = world_params["layers"][0]["width"];
//    int height = world_params["layers"][0]["height"];
    auto terrains = world_params["layers"][0]["data"];

    int i, j;
    for (i = 0; i < HEIGHT; i ++) {
        for (j = 0; j < WIDTH; j ++) {
            int pos = (WIDTH * i) + j;
            int terrain_type = terrains[pos];
            auto t = static_cast<Terrain>(terrain_type);
            matrix[j][i] = t;
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
    bool x_in_boundaries = (pos_x >= 0) && (pos_x < WIDTH),
         y_in_boundaries = (pos_y >= 0) && (pos_y < HEIGHT);

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
    return WIDTH;
}

const int World::getHeight() const {
    return HEIGHT;
}
