//
// Created by martinrosas on 4/7/20.
//

#ifndef ARGENTUM_MAP_STRUCTS_H
#define ARGENTUM_MAP_STRUCTS_H

#endif //ARGENTUM_MAP_STRUCTS_H

typedef struct {
    std::vector<std::vector<Terrain>> terrains;
    std::vector<player_t> players;
    std::vector<npc_t> npcs;
    std::vector<creature_t> creatures;
    std::vector<item_t> items;
    player_info_t player_info;
    player_t main_player;
} client_world_t;