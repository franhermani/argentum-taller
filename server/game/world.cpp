#include <random>
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
    for (auto& creature : creatures)
        delete creature;

    for (auto& npc : npcs)
        delete npc;

    for (auto& item : items)
        delete item;
}

void World::loadImpenetrableTerrains() {
    impenetrableTerrains.insert(TERRAIN_WALL);
    impenetrableTerrains.insert(TERRAIN_WATER);
    impenetrableTerrains.insert(TERRAIN_OUT_OF_BOUNDARIES);
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

// -------------------------------------------- //
// Metodos accedidos por threads (WorldMonitor) //
// -------------------------------------------- //

void World::update(const int ms) {
    for (auto& player : players)
        player->update(ms);

    for (auto& creature : creatures)
        creature->update(ms);
}

void World::addPlayer(Player* player) {
    players.push_back(player);
}

void World::removePlayer(const int id) {
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

std::vector<NPC *> World::getNPCs() const {
    return npcs;
}

std::vector<Player*> World::getPlayersAround(Player &player) {
    std::vector<Player*> players_around;

    for (auto& p : players)
        if (inPlayerBoundaries(player, p->posX, p->posY))
            players_around.push_back(p);

    return players_around;
}

std::vector<Creature*> World::getCreaturesAround(Player &player) {
    std::vector<Creature*> creatures_around;

    for (auto& c : creatures)
        if (inPlayerBoundaries(player, c->posX, c->posY))
            creatures_around.push_back(c);

    return creatures_around;
}

std::vector<Item*> World::getItemsAround(Player &player) {
    std::vector<Item*> items_around;

    for (auto& i : items)
        if (inPlayerBoundaries(player, i->posX, i->posY))
            items_around.push_back(i);

    return items_around;
}

const bool World::inPlayerBoundaries(Player &player,
        const int pos_x, const int pos_y) {
    int player_xi = player.posX - playerWidth/2,
        player_xf = player.posX + playerWidth/2,
        player_yi = player.posY - playerHeight/2,
        player_yf = player.posY + playerHeight/2;

    bool x_in_boundaries = (pos_x >= player_xi) && (pos_x < player_xf),
         y_in_boundaries = (pos_y >= player_yi) && (pos_y < player_yf);

    return x_in_boundaries && y_in_boundaries;
}

const int World::getWidth() const {
    return worldWidth;
}

const int World::getHeight() const {
    return worldHeight;
}

// ------------------------------------------- //
// Metodos accedidos por entidades del dominio //
// ------------------------------------------- //

const bool World::inMapBoundaries(const int pos_x, const int pos_y) {
    bool x_in_boundaries = (pos_x >= 0) && (pos_x < worldWidth),
         y_in_boundaries = (pos_y >= 0) && (pos_y < worldHeight);

    return x_in_boundaries && y_in_boundaries;
}

const bool World::inCollision(const int pos_x, const int pos_y) {
    // Terrenos impenetrables
    if (impenetrableTerrains.count(matrix[pos_y][pos_x]) > 0)
        return true;

    // Players
    for (auto& player : players)
        if (player->posX == pos_x && player->posY == pos_y)
            return true;

    // NPCs
    for (auto& npc : npcs)
        if (npc->posX == pos_x && npc->posY == pos_y)
            return true;

    // Criaturas
    for (auto& creature : creatures)
        if (creature->posX == pos_x && creature->posY == pos_y)
            return true;

    return false;
}

const bool World::itemInPosition(const int pos_x, const int pos_y) {
    size_t i;
    for (i = 0; i < items.size(); i ++)
        if (items[i]->posX == pos_x && items[i]->posY == pos_y)
            return true;

    return false;
}

void World::addItem(Item* item) {
    items.push_back(item);
}

Item* World::removeItem(const int pos_x, const int pos_y) {
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

Creature* World::getCreatureById(const int id) const {
    for (auto& creature : creatures)
        if (creature->id == id)
            return creature;

    return nullptr;
}

NPC* World::getNPCByPos(const int pos_x, const int pos_y) const {
    for (auto& npc : npcs)
        if (npc->posX == pos_x && npc->posY == pos_y)
            return npc;

    return nullptr;
}

const int World::getInventoryLength() const {
    return params.getConfigParams()["player"]["inventory"]["max_objects"];
}

const int World::getMaxLevelNewbie() const {
    return params.getConfigParams()["player"]["fair_play"]["min_level_newbie"];
}

const int World::getMaxLevelDiff() const {
    return params.getConfigParams()["player"]["fair_play"]["min_level_diff"];
}

// --------------------------------- //
// Metodos accedidos por GameManager //
// --------------------------------- //

void World::addNPC(NPC *npc) {
    npcs.push_back(npc);
}

void World::addCreature(Creature *creature) {
    creatures.push_back(creature);
}

// TODO: dentro de safe zones
std::vector<int> World::loadNPCPosition() {
    std::vector<int> pos = {0,0};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, worldWidth - 1);
    std::uniform_int_distribution<int> dist_y(0, worldHeight - 1);

    int new_x = dist_x(mt), new_y = dist_y(mt);
    while (inCollision(new_x, new_y)) {
        new_x = dist_x(mt);
        new_y = dist_y(mt);
    }
    pos[0] = new_x;
    pos[1] = new_y;

    return pos;
}

// TODO: fuera de safe zones
std::vector<int> World::loadCreaturePosition() {
    std::vector<int> pos = {0,0};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, worldWidth - 1);
    std::uniform_int_distribution<int> dist_y(0, worldHeight - 1);

    int new_x = dist_x(mt), new_y = dist_y(mt);
    while (inCollision(new_x, new_y)) {
        new_x = dist_x(mt);
        new_y = dist_y(mt);
    }
    pos[0] = new_x;
    pos[1] = new_y;

    return pos;
}
