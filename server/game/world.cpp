#include "world.h"

World::World(GameParams& params) : params(params) {
    json js;
    js = params.getWorldParams()["layers"][0];
    worldWidth = js["width"], worldHeight = js["height"];

    js = params.getConfigParams()["blocks_around_player"];
    playerWidth = js["width"], playerHeight = js["height"];

    loadImpenetrableTerrains();
    loadMatrix();
}

World::~World() {
    // TODO: delete npcs
    for (auto& item : items)
        delete item;
}

void World::loadImpenetrableTerrains() {
    impenetrableTerrains.insert(TERRAIN_WALL);
    impenetrableTerrains.insert(TERRAIN_WATER);
}

void World::loadMatrix() {
    json js = params.getWorldParams()["layers"][0];
    auto terrains = js["data"];

    matrix.resize(worldHeight);
    int i, j, pos, terrain_type;
    for (i = 0; i < worldHeight; i ++) {
        std::vector<Terrain> row;
        row.resize(worldWidth);
        matrix.push_back(row);
        for (j = 0; j < worldWidth; j ++) {
            pos = (worldWidth * i) + j;
            terrain_type = terrains[pos];
            matrix[i].push_back(static_cast<Terrain>(terrain_type));
        }
    }
}

// --------------------------------------------- //
// Metodos accedidos por WorldMonitor unicamente //
// --------------------------------------------- //

void World::update(int ms) {
    // TODO: update tmb a los npcs
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

const int World::getPlayerWidth() {
    return playerWidth;
}

const int World::getPlayerHeight() {
    return playerHeight;
}

std::vector<std::vector<Terrain>> World::getMatrix() const {
    return matrix;
}

std::vector<Player*> World::getPlayersAround(Player &player) {
    std::vector<Player*> players_around;

    for (auto& p : players)
        if (inPlayerBoundaries(player, p->posX, p->posY))
            players_around.push_back(p);

    return players_around;
}

bool World::inPlayerBoundaries(Player &player, int pos_x, int pos_y) {
    int player_xi = player.posX - playerWidth/2,
        player_xf = player.posX + playerWidth/2,
        player_yi = player.posY - playerHeight/2,
        player_yf = player.posY + playerHeight/2;

    bool x_in_boundaries = (pos_x >= player_xi) && (pos_x < player_xf),
         y_in_boundaries = (pos_y >= player_yi) && (pos_y < player_yf);

    return x_in_boundaries && y_in_boundaries;
}

// --------------------------------------------- //
// Metodos accedidos por Player y NPC unicamente //
// --------------------------------------------- //

bool World::inMapBoundaries(int pos_x, int pos_y) {
    bool x_in_boundaries = (pos_x >= 0) && (pos_x < worldWidth),
         y_in_boundaries = (pos_y >= 0) && (pos_y < worldHeight);

    return x_in_boundaries && y_in_boundaries;
}

bool World::inCollision(int pos_x, int pos_y) {
    // Terrenos impenetrables
    if (impenetrableTerrains.count(matrix[pos_y][pos_x]) > 0)
        return true;

    // Players
    for (auto& player : players)
        if (player->posX == pos_x && player->posY == pos_y)
            return true;

    // TODO: chequear lista de NPCs
    /*
    for (auto& npc : npcs)
        if (npc->posX == pos_x && npc->posY == pos_y)
            return true;
    */

    return false;
}

void World::addItem(Item* item) {
    items.push_back(item);
}

Item* World::removeItem(int pos_x, int pos_y) {
    size_t i;
    for (i = 0; i < items.size(); i ++)
        if (items[i]->posX == pos_x && items[i]->posY == pos_y) {
            Item* item = items[i];
            items.erase(items.begin() + i);
            return item;
        }
    return nullptr;
}

Player* World::getPlayerById(const int id) const {
    for (auto& player : players)
        if (player->id == id)
            return player;

    return nullptr;
}

const int World::getInventoryLength() const {
    return params.getConfigParams()["player"]["inventory"]["max_objects"];
}

// ------------------------------------------------ //
// Metodos accedidos por WorldMonitor, Player y NPC //
// ------------------------------------------------ //

const int World::getWidth() const {
    return worldWidth;
}

const int World::getHeight() const {
    return worldHeight;
}
