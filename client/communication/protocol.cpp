#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/debug.h"

#define SIZE_8                      sizeof(uint8_t)
#define SIZE_16                     sizeof(uint16_t)
#define SIZE_32                     sizeof(uint32_t)

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket) {}

void ClientProtocol::sendCommand(CommandDTO& command) {
    std::vector<char> byte_msg = command.serialize();
    socket.sendBytes(byte_msg.data(), byte_msg.size());
}

void ClientProtocol::sendPlayerInfo(const std::string& username,
        const uint8_t race_type, const uint8_t class_type) {
    // Longitud total
    size_t total_size = 3 * SIZE_8 + username.length();

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Longitud del username
    byte_msg[0] = 2 * SIZE_8 + username.length();

    // Raza
    byte_msg[1] = race_type;

    // Clase
    byte_msg[2] = class_type;

    // Username
    memcpy(&byte_msg[3], username.c_str(), username.length());

    socket.sendBytes(byte_msg.data(), byte_msg.size());
}


const int ClientProtocol::receiveUsernameConfirmation() {
    std::vector<char> code;
    int message_length = SIZE_8;

    code.resize(message_length);
    socket.receiveBytes(code.data(), message_length);
    return (int) code[0];
}

const int ClientProtocol::receiveUsernameId() {
    std::vector<char> byte_msg;
    uint16_t id;
    int message_length = SIZE_16;

    byte_msg.resize(message_length);
    socket.receiveBytes(byte_msg.data(), message_length);
    memcpy(&id, byte_msg.data(), message_length);
    return ntohs(id);
}

const std::vector<int> ClientProtocol::receiveBlocksAround() {
    std::vector<char> byte_msg;
    std::vector<int> blocks;
    int message_length = SIZE_16;

    byte_msg.resize(message_length);
    socket.receiveBytes(byte_msg.data(), message_length);

    blocks.resize(message_length);
    blocks[0] = (int) byte_msg[0];
    blocks[1] = (int) byte_msg[1];

    return std::move(blocks);
}


const std::vector<int> ClientProtocol::receiveMapDimensions() {
    std::vector<char> byte_msg;
    std::vector<int> blocks;
    int message_length = 2 * SIZE_16;

    byte_msg.resize(message_length);
    socket.receiveBytes(byte_msg.data(), message_length);

    blocks.resize(2* sizeof(int));
    uint16_t width;
    memcpy(&width, byte_msg.data(), SIZE_16);
    blocks[0] = ntohs(width);
    uint16_t height;
    memcpy(&height, byte_msg.data()+SIZE_16, SIZE_16);
    blocks[1] = ntohs(height);
    return std::move(blocks);
}

npcs_t ClientProtocol::receiveNPCs() {
    npcs_t n;

    // Recibo longitud del mensaje
    std::vector<char> length_buffer;
    length_buffer.resize(SIZE_16);
    socket.receiveBytes(length_buffer.data(), SIZE_16);

    uint16_t message_length;
    memcpy(&message_length, length_buffer.data(), SIZE_16);
    n.length = ntohs(message_length);

    // Recibo el mensaje
    std::vector<char> npcs_buffer;
    npcs_buffer.resize(n.length);
    socket.receiveBytes(npcs_buffer.data(), n.length);

    int bytes_advanced = 0;

    // Cantidad de NPCs
    uint16_t num_npcs;
    memcpy(&num_npcs, npcs_buffer.data() + bytes_advanced, SIZE_16);
    n.num_npcs = ntohs(num_npcs);
    bytes_advanced += SIZE_16;

    // Lista de NPCs
    std::vector<npc_t> npcs;
    npcs.resize(n.num_npcs * sizeof(npc_t));

    int i;
    for (i = 0; i < n.num_npcs; i ++) {
        npc_t npc;

        // Enum type del NPC
        uint8_t type;
        memcpy(&type, npcs_buffer.data() + bytes_advanced, SIZE_8);
        npc.type = type;
        bytes_advanced += SIZE_8;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, npcs_buffer.data() + bytes_advanced, SIZE_16);
        npc.pos.x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, npcs_buffer.data() + bytes_advanced, SIZE_16);
        npc.pos.y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // Enum type de la orientacion
        uint8_t orientation;
        memcpy(&orientation, npcs_buffer.data() + bytes_advanced, SIZE_8);
        npc.orientation = orientation;
        bytes_advanced += SIZE_8;

        npcs[i] = npc;
    }
    n.npcs = npcs;

    return std::move(n);
}

world_t ClientProtocol::receiveWorldUpdate() {
    world_t w;

    // Longitud del mensaje
    std::vector<char> length_buffer(SIZE_16, 0);
    socket.receiveBytes(length_buffer.data(), SIZE_16);

    uint16_t length;
    memcpy(&length, length_buffer.data(), SIZE_16);
    w.length = ntohs(length);

    int bytes_advanced = 0;

    // Mensaje
    std::vector<char> world_buffer(w.length,0);
    socket.receiveBytes(world_buffer.data(), w.length);

    // ---------------- //
    // Player principal //
    // ---------------- //

    // Mana actual
    uint16_t actual_mana;
    memcpy(&actual_mana, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.actual_mana = ntohs(actual_mana);
    bytes_advanced += SIZE_16;

    // Mana maxima
    uint16_t max_mana;
    memcpy(&max_mana, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.max_mana = ntohs(max_mana);
    bytes_advanced += SIZE_16;

    // Oro actual
    uint16_t actual_gold;
    memcpy(&actual_gold, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.actual_gold = ntohs(actual_gold);
    bytes_advanced += SIZE_16;

    // Oro maximo
    uint16_t max_gold;
    memcpy(&max_gold, world_buffer.data() + bytes_advanced, SIZE_16);
    w.player_info.max_gold = ntohs(max_gold);
    bytes_advanced += SIZE_16;

    // Experiencia actual del nivel
    uint32_t level_actual_exp;
    memcpy(&level_actual_exp, world_buffer.data() + bytes_advanced, SIZE_32);
    w.player_info.level_actual_experience = ntohl(level_actual_exp);
    bytes_advanced += SIZE_32;

    // Experiencia maxima del nivel
    uint32_t level_max_exp;
    memcpy(&level_max_exp, world_buffer.data() + bytes_advanced, SIZE_32);
    w.player_info.level_max_experience = ntohl(level_max_exp);
    bytes_advanced += SIZE_32;

    // Inventario
    uint8_t inventory_length;
    memcpy(&inventory_length, world_buffer.data() + bytes_advanced, SIZE_8);
    w.player_info.inventory.length = inventory_length;
    w.player_info.inventory.items.resize(inventory_length);
    bytes_advanced += SIZE_8;

    int i;
    for (i = 0; i < inventory_length; i ++) {
        uint8_t item_type;
        memcpy(&item_type, world_buffer.data() + bytes_advanced, SIZE_8);
        w.player_info.inventory.items[i] = item_type;
        bytes_advanced += SIZE_8;
    }

    // ------- //
    // Players //
    // ------- //

    // Cantidad de Players
    uint16_t num_players;
    memcpy(&num_players, world_buffer.data() + bytes_advanced, SIZE_16);
    w.num_players = ntohs(num_players);
    bytes_advanced += SIZE_16;

    // Lista de Players
    std::vector<player_t> players;
    players.resize(w.num_players * sizeof(player_t));

    for (i = 0; i < w.num_players; i ++) {
        player_t player;

        // Id
        uint16_t id;
        memcpy(&id, world_buffer.data() + bytes_advanced, SIZE_16);
        player.id = ntohs(id);
        bytes_advanced += SIZE_16;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, world_buffer.data() + bytes_advanced, SIZE_16);
        player.pos.x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, world_buffer.data() + bytes_advanced, SIZE_16);
        player.pos.y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // Vida actual
        uint16_t actual_life;
        memcpy(&actual_life, world_buffer.data() + bytes_advanced, SIZE_16);
        player.actual_life = ntohs(actual_life);
        bytes_advanced += SIZE_16;

        // Vida maxima
        uint16_t max_life;
        memcpy(&max_life, world_buffer.data() + bytes_advanced, SIZE_16);
        player.max_life = ntohs(max_life);
        bytes_advanced += SIZE_16;

        // Nivel
        uint16_t level;
        memcpy(&level, world_buffer.data() + bytes_advanced, SIZE_16);
        player.level = ntohs(level);
        bytes_advanced += SIZE_16;

        // Enum type de la orientacion
        uint8_t orientation;
        memcpy(&orientation, world_buffer.data() + bytes_advanced, SIZE_8);
        player.orientation = orientation;
        bytes_advanced += SIZE_8;

        // Enum type del estado
        uint8_t state;
        memcpy(&state, world_buffer.data() + bytes_advanced, SIZE_8);
        player.state = state;
        bytes_advanced += SIZE_8;

        // Enum type de la raza
        uint8_t race_type;
        memcpy(&race_type, world_buffer.data() + bytes_advanced, SIZE_8);
        player.race_type = race_type;
        bytes_advanced += SIZE_8;

        // Enum type de la clase
        uint8_t class_type;
        memcpy(&class_type, world_buffer.data() + bytes_advanced, SIZE_8);
        player.class_type = class_type;
        bytes_advanced += SIZE_8;

        // Enum type del arma
        uint8_t weapon;
        memcpy(&weapon, world_buffer.data() + bytes_advanced, SIZE_8);
        player.weapon = weapon;
        bytes_advanced += SIZE_8;

        // Enum type de la armadura
        uint8_t armor;
        memcpy(&armor, world_buffer.data() + bytes_advanced, SIZE_8);
        player.armor = armor;
        bytes_advanced += SIZE_8;

        // Enum type del casco
        uint8_t helmet;
        memcpy(&helmet, world_buffer.data() + bytes_advanced, SIZE_8);
        player.helmet = helmet;
        bytes_advanced += SIZE_8;

        // Enum type del escudo
        uint8_t shield;
        memcpy(&shield, world_buffer.data() + bytes_advanced, SIZE_8);
        player.shield = shield;
        bytes_advanced += SIZE_8;

        players[i] = player;

        if (debug) {
            std::cout << "\nPLAYER RECIBIDO\n" <<
            "Id: " << player.id << "\n" <<
            "Pos X: " << player.pos.x << "\n" <<
            "Pos Y: " << player.pos.y << "\n" <<
            "Vida actual: " << player.actual_life << "\n" <<
            "Vida maxima: " << player.max_life << "\n" <<
            "Nivel: " << player.level << "\n" <<
            "Orientacion: " << (int) player.orientation << "\n" <<
            "Estado: " << (int) player.state << "\n" <<
            "Raza: " << (int) player.race_type << "\n" <<
            "Clase: " << (int) player.class_type << "\n" <<
            "Arma: " << (int) player.weapon << "\n" <<
            "Armadura: " << (int) player.armor << "\n" <<
            "Casco: " << (int) player.helmet << "\n" <<
            "Escudo: " << (int) shield << "\n";
        }
    }
    w.players = players;

    // --------- //
    // Criaturas //
    // --------- //

    // Cantidad de Criaturas
    uint16_t num_creatures;
    memcpy(&num_creatures, world_buffer.data() + bytes_advanced, SIZE_16);
    w.num_creatures = ntohs(num_creatures);
    bytes_advanced += SIZE_16;

    // Lista de Criaturas
    std::vector<creature_t> creatures;
    creatures.resize(w.num_creatures * sizeof(creature_t));

    for (i = 0; i < w.num_creatures; i ++) {
        creature_t creature;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, world_buffer.data() + bytes_advanced, SIZE_16);
        creature.pos.x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, world_buffer.data() + bytes_advanced, SIZE_16);
        creature.pos.y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // Vida actual
        uint16_t actual_life;
        memcpy(&actual_life, world_buffer.data() + bytes_advanced, SIZE_16);
        creature.actual_life = ntohs(actual_life);
        bytes_advanced += SIZE_16;

        // Vida maxima
        uint16_t max_life;
        memcpy(&max_life, world_buffer.data() + bytes_advanced, SIZE_16);
        creature.max_life = ntohs(max_life);
        bytes_advanced += SIZE_16;

        // Nivel
        uint16_t level;
        memcpy(&level, world_buffer.data() + bytes_advanced, SIZE_16);
        creature.level = ntohs(level);
        bytes_advanced += SIZE_16;

        // Enum type del tipo
        uint8_t type;
        memcpy(&type, world_buffer.data() + bytes_advanced, SIZE_8);
        creature.type = type;
        bytes_advanced += SIZE_8;

        // Enum type de la orientacion
        uint8_t orientation;
        memcpy(&orientation, world_buffer.data() + bytes_advanced, SIZE_8);
        creature.orientation = orientation;
        bytes_advanced += SIZE_8;

        // Enum type del estado
        uint8_t state;
        memcpy(&state, world_buffer.data() + bytes_advanced, SIZE_8);
        creature.state = state;
        bytes_advanced += SIZE_8;

        creatures[i] = creature;

        /*
        if (debug) {
            std::cout << "\nCRIATURA RECIBIDA\n" <<
            "Pos X: " << (int) creature.pos.x << "\n" <<
            "Pos Y: " << (int) creature.pos.y << "\n" <<
            "Vida actual: " << (int) creature.actual_life << "\n" <<
            "Vida maxima: " << (int) creature.max_life << "\n" <<
            "Tipo: " << (int) creature.type << "\n" <<
            "Orientacion: " << (int) creature.orientation << "\n" <<
            "Estado: " << (int) creature.state << "\n";
        }
         */
    }
    w.creatures = creatures;

    // ----- //
    // Items //
    // ----- //

    // Cantidad de Items
    uint16_t num_items;
    memcpy(&num_items, world_buffer.data() + bytes_advanced, SIZE_16);
    w.num_items = ntohs(num_items);
    bytes_advanced += SIZE_16;

    // Lista de Items
    std::vector<item_t> items;
    items.resize(w.num_items * sizeof(item_t));

    for (i = 0; i < w.num_items; i ++) {
        item_t item;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, world_buffer.data() + bytes_advanced, SIZE_16);
        item.pos.x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, world_buffer.data() + bytes_advanced, SIZE_16);
        item.pos.y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // Enum type del item
        uint8_t item_type;
        memcpy(&item_type, world_buffer.data() + bytes_advanced, SIZE_8);
        item.type = item_type;
        bytes_advanced += SIZE_8;

        items[i] = item;
    }
    w.items = items;

    // ---- //
    // Oros //
    // ---- //

    // Cantidad de Oros
    uint16_t num_golds;
    memcpy(&num_golds, world_buffer.data() + bytes_advanced, SIZE_16);
    w.num_golds = ntohs(num_golds);
    bytes_advanced += SIZE_16;

    // Lista de Oros
    std::vector<gold_t> golds;
    golds.resize(w.num_golds * sizeof(gold_t));

    for (i = 0; i < w.num_golds; i ++) {
        gold_t gold;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, world_buffer.data() + bytes_advanced, SIZE_16);
        gold.pos.x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, world_buffer.data() + bytes_advanced, SIZE_16);
        gold.pos.y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // Cantidad
        uint16_t quantity;
        memcpy(&quantity, world_buffer.data() + bytes_advanced, SIZE_16);
        gold.quantity = ntohs(quantity);
        bytes_advanced += SIZE_16;

        golds[i] = gold;
    }
    w.golds = golds;

    // ------- //
    // Ataques //
    // ------- //

    // Cantidad de Ataques
    uint16_t num_attacks;
    memcpy(&num_attacks, world_buffer.data() + bytes_advanced, SIZE_16);
    w.num_attacks = ntohs(num_attacks);
    bytes_advanced += SIZE_16;

    // Lista de Ataques
    std::vector<attack_t> attacks;
    attacks.resize(w.num_attacks * sizeof(attack_t));

    for (i = 0; i < w.num_attacks; i ++) {
        attack_t attack;

        // Pos x en la matriz
        uint16_t pos_x;
        memcpy(&pos_x, world_buffer.data() + bytes_advanced, SIZE_16);
        attack.pos.x = ntohs(pos_x);
        bytes_advanced += SIZE_16;

        // Pos y en la matriz
        uint16_t pos_y;
        memcpy(&pos_y, world_buffer.data() + bytes_advanced, SIZE_16);
        attack.pos.y = ntohs(pos_y);
        bytes_advanced += SIZE_16;

        // Enum type de la orientacion
        uint8_t orientation;
        memcpy(&orientation, world_buffer.data() + bytes_advanced, SIZE_8);
        attack.orientation = orientation;
        bytes_advanced += SIZE_8;

        // Enum type del tipo
        uint8_t type;
        memcpy(&type, world_buffer.data() + bytes_advanced, SIZE_8);
        attack.type = type;
        bytes_advanced += SIZE_8;

        // 1 si esta colisionando, 0 si no
        uint8_t is_colliding;
        memcpy(&is_colliding, world_buffer.data() + bytes_advanced, SIZE_8);
        attack.is_colliding = is_colliding;
        bytes_advanced += SIZE_8;

        attacks[i] = attack;

        /*
        if (debug) {
            std::cout << "\nATAQUE RECIBIDO\n" <<
            "Pos X: " << (int) attack.pos.x << "\n" <<
            "Pos Y: " << (int) attack.pos.y << "\n" <<
            "Orientacion: " << (int) attack.orientation << "\n" <<
            "Tipo: " << (int) attack.type << "\n" <<
            "Colisionando: " << (int) attack.is_colliding << "\n";
        }
         */
    }
    w.attacks = attacks;

    return std::move(w);
}

list_t ClientProtocol::receiveItemsList() {
    list_t list;
    int static_part_size = SIZE_16 + SIZE_16 + SIZE_8;
    std::vector<char> item_static_buffer(static_part_size, 0);
    socket.receiveBytes(item_static_buffer.data(), item_static_buffer.size());

    int bytes_advanced = 0;

    uint8_t show_price;
    memcpy(&show_price, item_static_buffer.data() + bytes_advanced, SIZE_8);
    list.show_price = show_price;
    bytes_advanced += SIZE_8;

    uint16_t gold_quantity;
    memcpy(&gold_quantity, item_static_buffer.data() + bytes_advanced,
            SIZE_16);
    list.gold_quantity = ntohs(gold_quantity);
    bytes_advanced += SIZE_16;

    uint16_t num_items;
    memcpy(&num_items, item_static_buffer.data() + bytes_advanced, SIZE_16);
    list.num_items = ntohs(num_items);
    bytes_advanced += SIZE_16;

    if (list.num_items == 0)
        return list;

    bytes_advanced = 0;
    int size = (SIZE_8 + SIZE_16) * list.num_items;
    std::vector<char> item_buffer(size, 0);
    socket.receiveBytes(item_buffer.data(), item_buffer.size());

    std::vector<list_item_t> items;
    int i;
    for (i = 0; i < list.num_items; i ++) {
        list_item_t item;
        uint8_t type;
        memcpy(&type, item_buffer.data() + bytes_advanced, SIZE_8);
        item.type = type;
        bytes_advanced += SIZE_8;

        uint16_t price;
        memcpy(&price, item_buffer.data() + bytes_advanced, SIZE_16);
        item.price = ntohs(price);
        bytes_advanced += SIZE_16;

        items.push_back(item);
    }
    list.items = items;
    return list;
}

const std::string ClientProtocol::receiveGameMessage() {
    // Longitud del mensaje
    std::vector<char> length_buffer(SIZE_8, 0);
    socket.receiveBytes(length_buffer.data(), SIZE_8);

    int message_length = (int) length_buffer[0];
    if (message_length == 0) return "";

    // Mensaje
    std::vector<char> msg_buffer;
    msg_buffer.resize(message_length);
    socket.receiveBytes(msg_buffer.data(), message_length);

    std::string message(msg_buffer.data());
    return message;
}
