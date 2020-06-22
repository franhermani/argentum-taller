#ifndef WORLD_STRUCTS_H
#define WORLD_STRUCTS_H

#include <cstdint>
#include <vector>
#include "terrains.h"

typedef struct {
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint16_t id;                // Id
    uint8_t type;               // Enum type del item
} item_t;

typedef struct {
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint16_t id;                // Id
    uint8_t orientation;        // Enum type de la orientacion
    uint8_t type;               // Enum type de la criatura o npc
} npc_t;

typedef struct {
    uint16_t id;                // Id
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint8_t is_alive;           // 1 si esta vivo, 0 si no (fantasma)
    uint8_t orientation;        // Enum type de la orientacion
    uint8_t race_type;          // Enum type de la raza
    uint8_t class_type;         // Enum type de la clase
    uint8_t body_armor;         // Enum type de la armadura o vestimenta
    uint8_t head_armor;         // Enum type del casco o sombrero
    uint8_t weapon;             // Enum type del arma
} player_t;

typedef struct {
    uint8_t length;                 // Longitud de la lista de items
    std::vector<uint8_t> items;     // Lista de items (enum type)
} inventory_t;

typedef struct {
    uint16_t actual_life;           // Vida actual
    uint16_t max_life;              // Vida maxima
    uint16_t actual_mana;           // Mana actual
    uint16_t max_mana;              // Mana maxima
    uint16_t actual_gold;           // Oro actual
    uint16_t max_gold;              // Oro maximo
    uint16_t level;                 // Nivel
    uint32_t actual_experience;     // Experiencia
    inventory_t inventory;          // Inventario
} player_info_t;

typedef struct {
    uint16_t length;                // Longitud total del mensaje
    player_info_t player_info;      // Info particular del player del cliente
    uint16_t num_players;           // Cantidad de players en 'players'
    std::vector<player_t> players;  // Lista de structs 'player_t'
    uint16_t num_npcs;              // Cantidad de npcs en 'npcs'
    std::vector<npc_t> npcs;        // Lista de structs 'npc_t'
    uint16_t num_items;             // Cantidad de items en 'items'
    std::vector<item_t> items;      // Lista de structs 'item_t'
} world_t;

typedef struct {
    uint16_t length;                // Longitud total del mensaje
    uint16_t width;                 // Ancho de la matriz
    uint16_t height;                // Alto de la matriz
    std::vector<Terrain> terrains;  // Lista de structs 'terrain_t'
} matrix_t;

#endif // WORLD_STRUCTS_H
