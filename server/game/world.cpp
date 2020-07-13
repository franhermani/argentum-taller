#include <map>
#include <string>
#include "world.h"
#include "entities/npcs/priest.h"
#include "game_exception.h"

World::World(GameParams& params, ItemFactory& item_factory,
        std::map<int,ProtectedQueue<std::string>>& messagesQueuePerPlayer) :
params(params),
itemFactory(item_factory),
messagesQueuePerPlayer(messagesQueuePerPlayer) {
    json js;
    js = params.getWorldParams();
    worldWidth = js["width"], worldHeight = js["height"];

    js = params.getConfigParams()["blocks_around_player"];
    playerWidth = js["width"], playerHeight = js["height"];

    loadPriestsPositions();
    loadMerchantsPositions();
    loadBankersPositions();
    loadUnsafePositions();
    loadSafePositions();
    loadCemeteryPositions();
    loadImpenetrablePositions();
}

World::~World() {
    for (auto& creature : creatures)
        delete creature;

    for (auto& npc : npcs)
        delete npc;

    for (auto& item : items)
        delete item;

    for (auto& gold : golds)
        delete gold;

    for (auto& attack : attacks)
        delete attack;
}

void World::loadPriestsPositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][0]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        priestsPositions.push_back(pos);
    }
}

void World::loadMerchantsPositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][1]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        merchantsPositions.push_back(pos);
    }
}

void World::loadBankersPositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][2]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        bankersPositions.push_back(pos);
    }
}

void World::loadUnsafePositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][3]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        unsafePositions.push_back(pos);
    }
}

void World::loadSafePositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][4]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        safePositions.push_back(pos);
    }
}

void World::loadCemeteryPositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][5]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        cemeteryPositions.push_back(pos);
    }
}

void World::loadImpenetrablePositions() {
    std::vector<int> terrains = params.getWorldParams()["layers"][6]["data"];

    size_t i, row = 0;
    for (i = 0; i < terrains.size(); i ++) {
        if (i != 0 && i % worldWidth == 0)
            row ++;

        if (terrains[i] == 0)
            continue;

        position_t pos(i % worldWidth, row);
        impenetrablePositions.push_back(pos);
    }
}

const bool World::playerInPosition(position_t new_pos) {
    for (auto& player : players)
        if (player->pos == new_pos)
            return true;
    return false;
}

const bool World::creatureInPosition(position_t new_pos) {
    for (auto& creature : creatures)
        if (creature->pos == new_pos)
            return true;
    return false;
}

const bool World::NPCInPosition(position_t new_pos) {
    for (auto& npc : npcs)
        if (npc->pos == new_pos)
            return true;
    return false;
}

const bool World::itemInPosition(position_t new_pos) {
    for (auto& item : items)
        if (item->pos == new_pos)
            return true;
    return false;
}

const bool World::goldInPosition(position_t new_pos) {
    for (auto& gold : golds)
        if (gold->pos == new_pos)
            return true;
    return false;
}

// -------------------------------------------- //
// Metodos accedidos por threads (WorldMonitor) //
// -------------------------------------------- //

void World::update(const int ms) {
    removeRangeReachedAttacks();

    for (auto& player : players)
        player->update(ms);

    for (auto& creature : creatures)
        creature->update(ms);

    for (auto& attack : attacks) {
        attack->update(ms);

        try {
            attackInCollision(attack);
        } catch (GameException& e) {
            std::string message(e.what());
            messagesQueuePerPlayer[e.getPlayerId()].push(message);
        }
    }
}

void World::removeRangeReachedAttacks() {
    std::vector<Attack*> tmp;
    auto iter = attacks.begin();
    for (; iter != attacks.end(); ++iter) {
        if ((*iter)->rangeReached()) {
            delete (*iter);
        } else {
            tmp.push_back((*iter));
        }
    }
    attacks.swap(tmp);
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

std::vector<NPC*> World::getNPCs() const {
    return npcs;
}

std::vector<Player*> World::getPlayersAround(Player& player) {
    std::vector<Player*> players_around;

    for (auto& p : players)
        if (inPlayerBoundaries(player, p->pos))
            players_around.push_back(p);

    return players_around;
}

std::vector<Creature*> World::getCreaturesAround(Player& player) {
    std::vector<Creature*> creatures_around;

    for (auto& c : creatures)
        if (inPlayerBoundaries(player, c->pos))
            creatures_around.push_back(c);

    return creatures_around;
}

std::vector<Item*> World::getItemsAround(Player& player) {
    std::vector<Item*> items_around;

    for (auto& i : items)
        if (inPlayerBoundaries(player, i->pos))
            items_around.push_back(i);

    return items_around;
}

std::vector<Gold*> World::getGoldsAround(Player& player) {
    std::vector<Gold*> golds_around;

    for (auto& g : golds)
        if (inPlayerBoundaries(player, g->pos))
            golds_around.push_back(g);

    return golds_around;
}

std::vector<Attack*> World::getAttacksAround(Player& player) {
    std::vector<Attack*> attacks_around;

    for (auto& a : attacks)
        if (inPlayerBoundaries(player, a->pos))
            attacks_around.push_back(a);

    return attacks_around;
}

const bool World::inPlayerBoundaries(Player &player, position_t new_pos) {
    int player_xi = player.pos.x - playerWidth/2,
        player_xf = player.pos.x + playerWidth/2,
        player_yi = player.pos.y - playerHeight/2,
        player_yf = player.pos.y + playerHeight/2;

    bool x_in_boundaries = (new_pos.x >= player_xi) && (new_pos.x < player_xf),
         y_in_boundaries = (new_pos.y >= player_yi) && (new_pos.y < player_yf);

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

const bool World::inMapBoundaries(position_t new_pos) {
    bool x_in_boundaries = (new_pos.x >= 0) && (new_pos.x < worldWidth),
         y_in_boundaries = (new_pos.y >= 0) && (new_pos.y < worldHeight);

    return x_in_boundaries && y_in_boundaries;
}

const bool World::inImpenetrablePosition(position_t new_pos) {
    for (auto& p : impenetrablePositions)
        if (p == new_pos)
            return true;
    return false;
}

const bool World::inSafePosition(position_t new_pos) {
    for (auto& p : safePositions)
        if (p == new_pos)
            return true;
    return false;
}

const bool World::entityInCollision(position_t new_pos) {
    bool collision = inImpenetrablePosition(new_pos) ||
                     playerInPosition(new_pos) ||
                     creatureInPosition(new_pos) ||
                     NPCInPosition(new_pos);

    return collision;
}

void World::attackInCollision(Attack* new_attack) {
    LivingBeing* owner = new_attack->owner;
    position_t attack_pos = new_attack->pos;

    // Terrenos impenetrables
    if (inImpenetrablePosition(attack_pos)) {
        new_attack->collision();
        return;
    }

    // Zonas seguras
    if (inSafePosition(attack_pos)) {
        new_attack->collision();
        return;
    }

    // Players
    for (auto& p : players) {
        if (owner->id == p->id && dynamic_cast<Player*>(owner))
            continue;

        if (p->pos == attack_pos) {
            new_attack->collision();
            owner->attack(*p);
            return;
        }
    }

    // Criaturas
    for (auto& c : creatures) {
        if (owner->id == c->id && dynamic_cast<Creature*>(owner))
            continue;

        if (c->pos == attack_pos) {
            new_attack->collision();
            owner->attack(*c);
            return;
        }
    }

    // NPCs
    for (auto& npc : npcs)
        if (npc->pos == attack_pos) {
            new_attack->collision();
            return;
        }
}

const bool World::itemInCollision(position_t new_pos) {
    bool collision = inImpenetrablePosition(new_pos) ||
                     NPCInPosition(new_pos) ||
                     itemInPosition(new_pos) ||
                     goldInPosition(new_pos);

    return collision;
}

void World::addItem(Item *item) {
    items.push_back(item);
}

void World::addItem(const int type, position_t new_pos) {
    Item *item = itemFactory(type, new_pos);
    items.push_back(item);
}

Item* World::removeItem(position_t new_pos) {
    size_t i;
    for (i = 0; i < items.size(); i ++)
        if (items[i]->pos == new_pos) {
            Item* item = items[i];
            items.erase(items.begin() + i);
            return item;
        }
    return nullptr;
}

void World::addGold(Gold *gold) {
    golds.push_back(gold);
}

Gold* World::removeGold(position_t new_pos) {
    size_t i;
    for (i = 0; i < golds.size(); i ++)
        if (golds[i]->pos == new_pos) {
            Gold* gold = golds[i];
            golds.erase(golds.begin() + i);
            return gold;
        }
    return nullptr;
}

void World::addAttack(Attack* new_attack) {
    attacks.push_back(new_attack);
}

NPC* World::getNPCByPos(position_t new_pos) const {
    for (auto& npc : npcs)
        if (npc->pos == new_pos)
            return npc;

    return nullptr;
}

position_t World::getClosestPlayerPos(position_t new_pos) {
    position_t closest_pos(0,0);
    int min_distance = 2 * worldHeight, actual_distance;

    for (auto& player : players) {
        // TODO: buscar players dentro de un rango
        if (player->isDead() || player->isReviving ||
            inSafePosition(player->pos))
            continue;

        actual_distance = distanceInBlocks(new_pos, player->pos);

        if (actual_distance < min_distance) {
            min_distance = actual_distance;
            closest_pos = player->pos;
        }
    }
    return closest_pos;
}

const int World::distanceInBlocks(position_t pos1, position_t pos2) {
    return pos1.distance(pos2);
}

position_t World::getClosestPriestPos(position_t new_pos) {
    position_t closest_pos(0,0);
    int min_distance = 2 * worldHeight, actual_distance;

    for (auto& npc : npcs) {
        if (! dynamic_cast<Priest*>(npc))
            continue;

        actual_distance = distanceInBlocks(new_pos, npc->pos);

        if (actual_distance < min_distance) {
            min_distance = actual_distance;
            closest_pos = npc->pos;
        }
    }
    return closest_pos;
}

const int World::distanceInMsToClosestPriest(position_t new_pos,
        const int velocity) {
    position_t priest_pos = getClosestPriestPos(new_pos);
    int distance = distanceInBlocks(new_pos, priest_pos);
    return distance * velocity;
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

position_t World::loadPlayerPosition() {
    position_t new_pos = math.randomPosition(safePositions);

    while (entityInCollision(new_pos))
        new_pos = math.randomPosition(safePositions);

    return new_pos;
}

position_t World::loadCreaturePosition() {
    position_t new_pos = math.randomPosition(unsafePositions);

    while (entityInCollision(new_pos))
        new_pos = math.randomPosition(unsafePositions);

    return new_pos;
}

position_t World::loadCreaturePositionInCemetery() {
    position_t new_pos = math.randomPosition(cemeteryPositions);

    while (entityInCollision(new_pos))
        new_pos = math.randomPosition(cemeteryPositions);

    return new_pos;
}

const int World::getNumberOfPriests() const {
    return priestsPositions.size();
}

const int World::getNumberOfMerchants() const {
    return merchantsPositions.size();
}

const int World::getNumberOfBankers() const {
    return bankersPositions.size();
}

position_t World::loadPriestPosition() {
    position_t new_pos = priestsPositions.back();
    priestsPositions.pop_back();
    return new_pos;
}

position_t World::loadMerchantPosition() {
    position_t new_pos = merchantsPositions.back();
    merchantsPositions.pop_back();
    return new_pos;
}

position_t World::loadBankerPosition() {
    position_t new_pos = bankersPositions.back();
    bankersPositions.pop_back();
    return new_pos;
}
