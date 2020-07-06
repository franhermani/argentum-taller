#ifndef ARGENTUM_MAP_STRUCTS_H
#define ARGENTUM_MAP_STRUCTS_H
#include <vector>
typedef struct {
    std::vector<std::vector<Terrain>> terrains;
    std::vector<player_t> players;
    std::vector<npc_t> npcs;
    std::vector<creature_t> creatures;
    std::vector<item_t> items;
    std::vector<gold_t> golds;
    player_info_t player_info;
    player_t main_player;
} client_world_t;

#endif //ARGENTUM_MAP_STRUCTS_H
