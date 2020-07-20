
#include "map.h"
#include <vector>
#include <iostream>
#include <utility>
#include "exception.h"
#include <map>
#include "../../common/defines/commands.h"
#include "../../common/defines/npcs.h"
#include "../sdl/render_structs.h"

// constructor
Map::Map() {
    interactingWithNpc = false;
}
// destructor
Map::~Map() {}

void Map::updateWorld(world_t receivedWorld, list_t received_list) {
    world.players = std::move(receivedWorld.players);
    world.num_players = std::move(receivedWorld.num_players);
    world.player_info = std::move(receivedWorld.player_info);
    mainPlayer = getMainPlayer();
    world.creatures = std::move(receivedWorld.creatures);
    world.num_creatures = std::move(receivedWorld.num_creatures);
    world.items = std::move(receivedWorld.items);
    world.num_items = std::move(receivedWorld.num_items);
    world.attacks = std::move(receivedWorld.attacks);
    world.num_attacks = std::move(receivedWorld.num_attacks);
    world.golds = std::move(receivedWorld.golds);
    world.num_golds = std::move(receivedWorld.num_golds);
    if ((not interactingWithNpc) || (interactingWithNpc &&
                received_list.num_items != 0))
        list = std::move(received_list);
}


void Map::initialize(int received_id,
        std::vector<int>& blocks_around,
        npcs_t& received_npcs, std::vector<int>& map_dimensions) {
    playerVisionWidth = blocks_around[0];
    playerVisionHeight = blocks_around[1];
    username_id = received_id;
    npcs = std::move(received_npcs);
    mapDimensions = std::move(map_dimensions);
}


player_t Map::getMainPlayer() {
    for (int i=0; i<world.num_players; i++) {
        if (username_id == world.players[i].id) {
            return world.players[i];
        }
    }
    throw MapException("main player not found");
}


int Map::getPlayerXStart(player_t& player) {
    int x_start = player.pos.x - playerVisionWidth/2;
    if (x_start < 0) return 0;
    return x_start;
}


int Map::getPlayerYStart(player_t& player) {
    int y_start = player.pos.y - playerVisionHeight/2;
    if (y_start < 0) return 0;
    return y_start;
}


int Map::getPlayerXEnd(player_t& player) {
    int x_finish = player.pos.x  + (playerVisionWidth / 2) + 1;
    if (x_finish >= mapDimensions[0]) return mapDimensions[0];
    return x_finish;
}

int Map::getPlayerYEnd(player_t& player) {
    int y_finish = player.pos.y  + (playerVisionHeight / 2) + 1;
    if (y_finish >= mapDimensions[1]) return mapDimensions[1];
    return y_finish;
}

std::vector<player_t> Map::findRenderablePlayers() {
    std::vector<player_t> visible_players;
    for (auto& player: world.players) {
        if (not betweenPlayerBorders(player.pos.x, player.pos.y)) {
            continue;
        } else {
            player_t converted_player = player;
            converted_player.pos.x = player.pos.x -
                    getPlayerXStart(mainPlayer);
            if (converted_player.pos.x < 0) converted_player.pos.x = 0;
            converted_player.pos.y = player.pos.y -
                    getPlayerYStart(mainPlayer);
            if (converted_player.pos.y < 0) converted_player.pos.y = 0;
            visible_players.push_back(converted_player);
        }
    }
    return visible_players;
}

int Map::betweenPlayerBorders(int pos_x, int pos_y) {
    int x_start, y_start, x_finish, y_finish;
    x_start = getPlayerXStart(mainPlayer);
    y_start = getPlayerYStart(mainPlayer);
    x_finish = getPlayerXEnd(mainPlayer);
    y_finish = getPlayerYEnd(mainPlayer);
    return ((pos_x >= x_start) &&  (pos_x <= x_finish)
    && (pos_y >= y_start) && (pos_y <= y_finish));
}

//todo ver que hacemos con estas 2
int Map::getNewBordersXPosition(int pos_x, player_t& main_player) {
    int pos;
    pos = pos_x - getPlayerXStart(main_player);
    if (pos < 0) pos = 0;
    return pos;
}
int Map::getNewBordersYPosition(int pos_y, player_t& main_player) {
    int pos;
    pos = pos_y - getPlayerYStart(main_player);
    if (pos < 0) pos = 0;
    return pos;
}

std::vector<npc_t> Map::findRenderableNpcs() {
    std::vector<npc_t> visible_npcs;
    for (auto& npc: npcs.npcs) {
        if (not betweenPlayerBorders(npc.pos.x, npc.pos.y)) {
            continue;
        } else {
            npc_t converted_npc = npc;
            converted_npc.pos.x = npc.pos.x - getPlayerXStart(mainPlayer);
            if (converted_npc.pos.x < 0) converted_npc.pos.x = 0;
            converted_npc.pos.y = npc.pos.y - getPlayerYStart(mainPlayer);
            if (converted_npc.pos.y < 0) converted_npc.pos.y = 0;
            visible_npcs.push_back(converted_npc);
        }
    }
    return visible_npcs;
}



std::vector<creature_t> Map::findRenderableCreatures() {
    std::vector<creature_t> visible_creatures;
    for (auto& creature: world.creatures) {
        if (not betweenPlayerBorders(creature.pos.x, creature.pos.y)) {
            continue;
        } else {
            creature_t converted_creature = creature;
            converted_creature.pos.x = creature.pos.x -
                    getPlayerXStart(mainPlayer);
            if (converted_creature.pos.x < 0) converted_creature.pos.x = 0;
            converted_creature.pos.y = creature.pos.y -
                    getPlayerYStart(mainPlayer);
            if (converted_creature.pos.y < 0) converted_creature.pos.y = 0;
            visible_creatures.push_back(converted_creature);
        }
    }
    return visible_creatures;
}

std::vector<gold_t> Map::findRenderableGolds() {
    std::vector<gold_t> visible_gold;
    for (auto& gold: world.golds) {
        if (not betweenPlayerBorders(gold.pos.x, gold.pos.y)) {
            continue;
        } else {
            gold_t converted_gold = gold;
            converted_gold.pos.x = gold.pos.x - getPlayerXStart(mainPlayer);
            if (converted_gold.pos.x < 0) converted_gold.pos.x = 0;
            converted_gold.pos.y = gold.pos.y - getPlayerYStart(mainPlayer);
            if (converted_gold.pos.y < 0) converted_gold.pos.y = 0;
            visible_gold.push_back(converted_gold);
        }
    }
    return visible_gold;
}


std::vector<attack_t> Map::findRenderableAttacks() {
    std::vector<attack_t> visible_attacks;
    for (auto& attack: world.attacks) {
        if (not betweenPlayerBorders(attack.pos.x, attack.pos.y)) {
            continue;
        } else {
            attack_t converted_attack = attack;
            converted_attack.pos.x = attack.pos.x -
                    getPlayerXStart(mainPlayer);
            if (converted_attack.pos.x < 0) converted_attack.pos.x = 0;
            converted_attack.pos.y = attack.pos.y -
                    getPlayerYStart(mainPlayer);
            if (converted_attack.pos.y < 0) converted_attack.pos.y = 0;
            visible_attacks.push_back(converted_attack);
        }
    }
    return visible_attacks;
}



std::vector<item_t> Map::findRenderableItems() {
    std::vector<item_t> visible_items;
    for (auto& item: world.items) {
        if (not betweenPlayerBorders(item.pos.x, item.pos.y)) {
            continue;
        } else {
            item_t converted_item = item;
            converted_item.pos.x = item.pos.x - getPlayerXStart(mainPlayer);
            if (converted_item.pos.x < 0) converted_item.pos.x = 0;
            converted_item.pos.y = item.pos.y - getPlayerYStart(mainPlayer);
            if (converted_item.pos.y < 0) converted_item.pos.y = 0;
            visible_items.push_back(converted_item);
        }
    }
    return visible_items;
}


int Map::getPlayerVisionWidth() {
    return playerVisionWidth;
}
int Map::getPlayerVisionHeight() {
    return playerVisionHeight;
}

std::vector<int> Map::getDimensions() {
    return mapDimensions;
}

std::vector<int> Map::getPositionLookingAt() {
    std::vector<int> position;
    if (mainPlayer.orientation == LEFT) {
        position.push_back(mainPlayer.pos.x - 1);
        position.push_back(mainPlayer.pos.y);
    } else if (mainPlayer.orientation == RIGHT) {
        position.push_back(mainPlayer.pos.x + 1);
        position.push_back(mainPlayer.pos.y);
    } else if (mainPlayer.orientation == UP) {
        position.push_back(mainPlayer.pos.x);
        position.push_back(mainPlayer.pos.y - 1);
    } else {
        position.push_back(mainPlayer.pos.x);
        position.push_back(mainPlayer.pos.y + 1);
    }
    return std::move(position);
}

std::vector<int> Map::getPriestLookingAt() {
    std::vector<int> looking_at = getPositionLookingAt();
    for (int i=0; i<npcs.length; i++) {
        if (npcs.npcs[i].type==PRIEST
            and npcs.npcs[i].pos.x == looking_at[0]
            and npcs.npcs[i].pos.y == looking_at[1])
            return std::move(looking_at);
    }
    throw MapException("No se encontro priest");
}


std::vector<int> Map::getItemStandingAt() {
    std::vector<int> player_position = {mainPlayer.pos.x, mainPlayer.pos.y};
    for (int i=0; i<world.num_items; i++) {
        if ((world.items[i].pos.x == player_position[0])
            && (world.items[i].pos.y == player_position[1]))
            return std::move(player_position);
    }
    throw MapException("No se encontro item");
}


std::vector<int> Map::getGoldStandingAt() {
    std::vector<int> player_position = {mainPlayer.pos.x, mainPlayer.pos.y};
    for (int i=0; i<world.num_golds; i++) {
        if ((world.golds[i].pos.x == player_position[0])
            && (world.golds[i].pos.y == player_position[1]))
            return std::move(player_position);
    }
    throw MapException("No se encontro gold");
}


void Map::interact() {
    interactingWithNpc = true;
}
void Map::uninteract() {
    interactingWithNpc = false;
}
int Map::isInteracting() {
    return interactingWithNpc;
}

std::vector<int> Map::getNpcLookingAt() {
    std::vector<int> looking_at = getPositionLookingAt();
    for (int i=0; i<npcs.length; i++) {
        if (npcs.npcs[i].pos.x == looking_at[0]
            and npcs.npcs[i].pos.y == looking_at[1]) {
            return std::move(looking_at);
        }
    }
    throw MapException("No hay ningun npc en la posicion solicitada");
}

std::map<int, float> Map::getPercentages() {
    return {{LIFE, ((float) mainPlayer.actual_life)/
                           mainPlayer.max_life},
    {MANA, ((float) world.player_info.actual_mana)/
                world.player_info.max_mana},
    {EXPERIENCE, ((float) world.player_info.level_actual_experience)/
                world.player_info.level_max_experience}};
}


client_world_t Map::getCurrentWorld() {
    client_world_t current_world;
    current_world.player_info = world.player_info;
    current_world.main_player = mainPlayer;
    current_world.players = findRenderablePlayers();
    current_world.items = findRenderableItems();
    current_world.golds = findRenderableGolds();
    current_world.creatures = findRenderableCreatures();
    current_world.npcs = findRenderableNpcs();
    current_world.percentages = getPercentages();
    current_world.attacks = findRenderableAttacks();
    current_world.list = list;

    return std::move(current_world);
}
