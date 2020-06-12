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

void World::update(int ms) {
    // TODO: ...
}
