
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
    mainPlayer = findMainPlayer();
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

template<typename T>
std::vector<T> Map::findVisible(std::vector<T> vec) {
    std::vector<T> visible_elems;
    for (auto& elem: vec) {
        if (not betweenPlayerBorders(elem.pos.x, elem.pos.y)) {
            continue;
        } else {
            T converted_elem = elem;
            converted_elem.pos.x = getNewBordersXPosition(elem.pos.x, mainPlayer);
            converted_elem.pos.y = getNewBordersYPosition(elem.pos.y, mainPlayer);
            visible_elems.push_back(converted_elem);
        }
    }
    return visible_elems;
}

player_t Map::findMainPlayer() {
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



int Map::betweenPlayerBorders(int pos_x, int pos_y) {
    int x_start, y_start, x_finish, y_finish;
    x_start = getPlayerXStart(mainPlayer);
    y_start = getPlayerYStart(mainPlayer);
    x_finish = getPlayerXEnd(mainPlayer);
    y_finish = getPlayerYEnd(mainPlayer);
    return ((pos_x >= x_start) &&  (pos_x <= x_finish)
    && (pos_y >= y_start) && (pos_y <= y_finish));
}

uint16_t Map::getNewBordersXPosition(uint16_t pos_x, player_t& main_player) {
    uint16_t pos;
    pos = pos_x - getPlayerXStart(main_player);
    if (pos < 0) pos = 0;
    return pos;
}
uint16_t Map::getNewBordersYPosition(uint16_t pos_y, player_t& main_player) {
    uint16_t pos;
    pos = pos_y - getPlayerYStart(main_player);
    if (pos < 0) pos = 0;
    return pos;
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
    current_world.players = findVisible(world.players);
    current_world.items = findVisible(world.items);
    current_world.golds = findVisible(world.golds);
    current_world.creatures = findVisible(world.creatures);
    current_world.npcs = findVisible(npcs.npcs);
    current_world.percentages = getPercentages();
    current_world.attacks = findVisible(world.attacks);
    current_world.list = list;
    return std::move(current_world);
}
