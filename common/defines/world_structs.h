#ifndef WORLD_STRUCTS_H
#define WORLD_STRUCTS_H

#include <cstdint>
#include <vector>
#include "terrains.h"

// ---------------------- //
// Listado de items y oro //
// ---------------------- //

typedef struct {
    uint8_t type;                   // Enum type del item
    uint16_t price;                 // Precio del item
} list_item_t;

typedef struct {
    uint8_t show_price;             // 1 si muestra precio, 0 si no
    uint16_t gold_quantity;         // Cantidad de oro
    uint16_t num_items;             // Cantidad de items en 'list_item_t'
    std::vector<list_item_t> items; // Lista de structs 'list_item_t'
} list_t;

// -------------- //
// Info del mundo //
// -------------- //

typedef struct {
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint8_t orientation;        // Enum type de la orietntacion
    uint8_t type;               // Enum type del tipo de ataque
    uint8_t is_colliding;       // 1 si esta colisionando, 0 si no
} attack_t;

typedef struct {
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint16_t quantity;          // Cantidad de oro
} gold_t;

typedef struct {
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint8_t type;               // Enum type del item
} item_t;

typedef struct {
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint16_t actual_life;       // Vida actual
    uint16_t max_life;          // Vida maxima
    uint16_t level;             // Nivel
    uint8_t type;               // Enum type del tipo de criatura
    uint8_t orientation;        // Enum type de la orientacion
} creature_t;

typedef struct {
    uint16_t id;                // Id
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint16_t actual_life;       // Vida actual
    uint16_t max_life;          // Vida maxima
    uint16_t level;             // Nivel
    uint8_t is_alive;           // 1 si esta vivo, 0 si no (fantasma)
    uint8_t is_meditating;      // 1 si esta meditando, 0 si no
    uint8_t is_reviving;        // 1 si esta reviviendo, 0 si no
    uint8_t orientation;        // Enum type de la orientacion
    uint8_t race_type;          // Enum type de la raza
    uint8_t class_type;         // Enum type de la clase
    uint8_t weapon;             // Enum type del arma
    uint8_t armor;              // Enum type del armadura
    uint8_t helmet;             // Enum type del casco
    uint8_t shield;             // Enum type del escudo
} player_t;

typedef struct {
    uint8_t length;                 // Longitud de la lista de items
    std::vector<uint8_t> items;     // Lista de items (enum type)
} inventory_t;

typedef struct {
    uint16_t actual_mana;           // Mana actual
    uint16_t max_mana;              // Mana maxima
    uint16_t actual_gold;           // Oro actual
    uint16_t max_gold;              // Oro maximo
    uint32_t actual_experience;     // Experiencia
    inventory_t inventory;          // Inventario
} player_info_t;

typedef struct {
    uint16_t life;                  // Porcentaje de vida
    uint16_t mana;                  // Porcentaje de mana
    uint16_t experience;            // Porcentaje de experiencia
} player_percentages_t;


typedef struct {
    uint16_t length;                    // Longitud total del mensaje
    player_info_t player_info;          // Info del player del cliente
    uint16_t num_players;               // Cantidad de players en 'players'
    std::vector<player_t> players;      // Lista de structs 'player_t'
    uint16_t num_creatures;             // Cantidad de criaturas en 'creatures'
    std::vector<creature_t> creatures;  // Lista de structs 'npc_t'
    uint16_t num_items;                 // Cantidad de items en 'items'
    std::vector<item_t> items;          // Lista de structs 'item_t'
    uint16_t num_golds;                 // Cantidad de oros en 'golds'
    std::vector<gold_t> golds;          // Lista de structs 'gold_t'
    uint16_t num_attacks;               // Cantidad de ataques en 'attacks'
    std::vector<attack_t> attacks;      // Lista de structs 'attack_t'
} world_t;

// ------------- //
// Lista de NPCs //
// ------------- //

typedef struct {
    uint8_t type;               // Enum type del tipo de NPC
    uint16_t pos_x;             // Pos x en la matriz
    uint16_t pos_y;             // Pos y en la matriz
    uint8_t orientation;        // Enum type de la orientacion
} npc_t;

typedef struct {
    uint16_t length;            // Longitud total del mensaje
    uint16_t num_npcs;          // Cantidad de npcs en 'npcs'
    std::vector<npc_t> npcs;    // Lista de structs 'npc_t'
} npcs_t;

// ------------------ //
// Matriz de terrenos //
// ------------------ //

typedef struct {
    uint16_t length;                // Longitud total del mensaje
    uint16_t width;                 // Ancho de la matriz
    uint16_t height;                // Alto de la matriz
    std::vector<Terrain> terrains;  // Lista de structs 'terrain_t'
} matrix_t;

#endif // WORLD_STRUCTS_H
