#ifndef WORLD_STRUCTS_H
#define WORLD_STRUCTS_H

#include <cstdint>

typedef struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t id;
    uint8_t type;
} item_t;

typedef struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t id;
    uint8_t orientation;
    uint8_t type;
} npc_t;

typedef struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t id;
    uint8_t is_alive;
    uint8_t orientation;
    uint8_t race_type;
    uint8_t class_type;
    uint8_t body_armor;
    uint8_t head_armor;
    uint8_t weapon;
} player_t;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t* terrains;
} matrix_t;

typedef struct {
    uint32_t length;
    matrix_t matrix;
    player_t* players;
    npc_t* npcs;
    item_t* items;
} world_t;

#endif // WORLD_STRUCTS_H
