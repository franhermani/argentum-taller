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

// TODO: ver quien crea y destruye a los GameObjects
void World::addGameObject(GameObject* game_object) {
    gameObjects.push_back(game_object);
}

void World::removeGameObject(int id) {
    for (auto object : gameObjects) {
        if (object->id == id) {
            // TODO: eliminar objeto
        }
    }
}

bool World::detectCollision(int pos_x, int pos_y) {
    for (auto object : gameObjects)
        if (object->posX == pos_x && object->posY == pos_y) {
            if (object->isImpenetrable) return true;
        }
    return false;
}

void World::update(int ms) {
    for (auto object : gameObjects) object->update(ms);
}
