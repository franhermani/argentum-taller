#include <string>
#include <vector>
#include "protocol.h"
#include "../../common/defines/debug.h"

#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)
#define SIZE_32     sizeof(uint32_t)

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

const std::vector<char> ServerProtocol::receivePlayerInfo() {
    std::vector<char> arguments;
    char buffer1[SIZE_8];
    socket.receiveBytes(buffer1, SIZE_8);

    int length = buffer1[0];
    arguments.resize(length);
    socket.receiveBytes(arguments.data(), arguments.size());

    return arguments;
}

Command* ServerProtocol::receiveCommand(Player& player) {
    std::vector<char> arguments;
    char buffer1[SIZE_8], buffer2[SIZE_8];

    socket.receiveBytes(buffer1, SIZE_8);
    socket.receiveBytes(buffer2, SIZE_8);

    int type = buffer1[0], length = buffer2[0];

    if (length > 0) {
        arguments.resize(length);
        socket.receiveBytes(arguments.data(), arguments.size());
    }

    if (debug)
        std::cout << "Recibido el comando tipo " << type << "\n";

    return commandFactory(player, type, arguments);
}

void ServerProtocol::sendUsernameConfirmation(int code) {
    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_8);
    byte_msg[0] = code;
    socket.sendBytes(byte_msg.data(), byte_msg.size());
}

void ServerProtocol::sendUsernameId(Player& player) {
    uint32_t player_id = htons(player.id);
    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16);
    memcpy(&byte_msg[0], &player_id, SIZE_16);
    socket.sendBytes(byte_msg.data(), byte_msg.size());
}


void ServerProtocol::sendBlocksAround(int width, int height) {
    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16);
    byte_msg[0] = width;
    byte_msg[1] = height;
    socket.sendBytes(byte_msg.data(), byte_msg.size());
}

void ServerProtocol::sendMatrix(WorldMonitor &world_monitor) {
    std::vector<std::vector<Terrain>> matrix = world_monitor.getMatrix();
    int width = world_monitor.getWidth();
    int height = world_monitor.getHeight();
    int matrix_length = width * height;

    // ------------------------- //
    // Carga del struct matrix_t //
    // ------------------------- //

    matrix_t m;
    m.length = htons(2 * SIZE_16 + matrix_length * SIZE_8);
    m.width = htons(width);
    m.height = htons(height);

    // ------------------------- //
    // Carga del struct byte_msg //
    // ------------------------- //

    std::vector<char> byte_msg;
    byte_msg.resize(3 * SIZE_16 + matrix_length);
    memcpy(&byte_msg[0], &m.length, SIZE_16);
    memcpy(&byte_msg[2], &m.width, SIZE_16);
    memcpy(&byte_msg[4], &m.height, SIZE_16);

    int i, j, k = 0;
    for (i = 0; i < height; i ++) {
        for (j = 0; j < width; j ++) {
            byte_msg[6+(k++)] = matrix[i][j];
        }
    }
    socket.sendBytes(byte_msg.data(), byte_msg.size());
}

void ServerProtocol::sendNPCs(WorldMonitor &world_monitor) {
    std::vector<NPC*> npcs = world_monitor.getNPCs();
    uint16_t num_npcs = npcs.size();

    // Longitud total del mensaje
    uint16_t message_length = SIZE_16 + num_npcs * (2 * SIZE_16 + 2 * SIZE_8);

    // ----------------------- //
    // Carga del struct npcs_t //
    // ----------------------- //

    npcs_t n;
    n.length = htons(message_length);

    // Cantidad de NPCs
    n.num_npcs = htons(num_npcs);
    n.npcs.resize(num_npcs * sizeof(npc_t));

    // Lista de NPCs
    int i;
    for (i = 0; i < num_npcs; i ++) {
        n.npcs[i].type = npcs[i]->type;
        n.npcs[i].pos_x = htons(npcs[i]->posX);
        n.npcs[i].pos_y = htons(npcs[i]->posY);
        n.npcs[i].orientation = npcs[i]->orientation;
    }

    // ------------------------- //
    // Carga del struct byte_msg //
    // ------------------------- //

    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16 + message_length);

    int pos = 0;
    memcpy(&byte_msg[pos], &n.length, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &n.num_npcs, SIZE_16);
    for (i = 0; i < num_npcs; i ++) {
        memcpy(&byte_msg[pos+=SIZE_16], &n.npcs[i].type, SIZE_8);
        memcpy(&byte_msg[pos+=SIZE_8], &n.npcs[i].pos_x, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &n.npcs[i].pos_y, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &n.npcs[i].orientation, SIZE_8);
        pos -= SIZE_8;
    }
    socket.sendBytes(byte_msg.data(), byte_msg.size());

    if (debug) {
        std::cout << "NPCs enviados:\n";
        for (char& c : byte_msg)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }
}

void ServerProtocol::sendWorldUpdate(WorldMonitor& world_monitor,
        Player& player) {
    world_t w;
    std::vector<Player*> players = world_monitor.getPlayersAround(player);
    std::vector<Creature*> creatures = world_monitor.
            getCreaturesAround(player);
    std::vector<Item*> items = world_monitor.getItemsAround(player);
    std::vector<Gold*> golds = world_monitor.getGoldsAround(player);
    std::vector<Attack*> attacks = world_monitor.getAttacksAround(player);

    // Longitudes variables
    uint8_t inventory_length = player.inventory.numItems;
    uint16_t num_players = players.size();
    uint16_t num_creatures = creatures.size();
    uint16_t num_items = items.size();
    uint16_t num_golds = golds.size();
    uint16_t num_attacks = attacks.size();

    // Longitud total del mensaje
    size_t message_length =
            // player_info_t
            4 * SIZE_16 + SIZE_32 +

            // inventory_t
            SIZE_8 + inventory_length * SIZE_8 +

            // player_t
            SIZE_16 + num_players * (6 * SIZE_16 + 10 * SIZE_8) +

            // creature_t
            SIZE_16 + num_creatures * (5 * SIZE_16 + 2 * SIZE_8) +

            // item_t
            SIZE_16 + num_items * (3 * SIZE_16) +

            // gold_t
            SIZE_16 + num_golds * (3 * SIZE_16) +

            // attack_t
            SIZE_16 + num_attacks * (2 * SIZE_16 + 3 * SIZE_8);

    // ------------------------ //
    // Carga del struct world_t //
    // ------------------------ //

    // Longitud total mensaje
    w.length = htons(message_length);

    // Info particular del Player del cliente
    w.player_info.actual_mana = htons(player.actualMana);
    w.player_info.max_mana = htons(player.maxMana);
    w.player_info.actual_gold = htons(player.actualGold);
    w.player_info.max_gold = htons(player.maxSafeGold);
    w.player_info.actual_experience = htonl(player.actualExperience);

    // Lista de Players (incluido el del cliente)
    w.num_players = htons(num_players);
    w.players.resize(num_players * sizeof(player_t));

    int i;
    for (i = 0; i < num_players; i ++) {
        w.players[i].id = htons(players[i]->id);
        w.players[i].pos_x = htons(players[i]->posX);
        w.players[i].pos_y = htons(players[i]->posY);
        w.players[i].actual_life = htons(players[i]->actualLife);
        w.players[i].max_life = htons(players[i]->maxLife);
        w.players[i].level = htons(players[i]->level);
        w.players[i].is_alive = players[i]->isAlive ? 1 : 0;
        w.players[i].is_meditating = players[i]->isMeditating ? 1 : 0;
        w.players[i].is_reviving = players[i]->isReviving ? 1 : 0;
        w.players[i].orientation = players[i]->orientation;
        w.players[i].race_type = players[i]->raceType;
        w.players[i].class_type = players[i]->classType;
        w.players[i].weapon = players[i]->weapon ?
                              players[i]->weapon->type : NO_ITEM_EQUIPPED;
        w.players[i].armor = players[i]->armor ?
                             players[i]->armor->type : NO_ITEM_EQUIPPED;
        w.players[i].helmet = players[i]->helmet ?
                              players[i]->helmet->type : NO_ITEM_EQUIPPED;
        w.players[i].shield = players[i]->shield ?
                              players[i]->shield->type : NO_ITEM_EQUIPPED;
    }

    // Lista de Criaturas
    w.num_creatures = htons(num_creatures);
    w.creatures.resize(num_creatures * sizeof(creature_t));

    for (i = 0; i < num_creatures; i ++) {
        w.creatures[i].pos_x = htons(creatures[i]->posX);
        w.creatures[i].pos_y = htons(creatures[i]->posY);
        w.creatures[i].actual_life = htons(creatures[i]->actualLife);
        w.creatures[i].max_life = htons(creatures[i]->maxLife);
        w.creatures[i].level = htons(creatures[i]->level);
        w.creatures[i].type = creatures[i]->type;
        w.creatures[i].orientation = creatures[i]->orientation;
    }

    // Lista de Items
    w.num_items = htons(num_items);
    w.items.resize(num_items * sizeof(item_t));

    for (i = 0; i < num_items; i ++) {
        w.items[i].pos_x = htons(items[i]->posX);
        w.items[i].pos_y = htons(items[i]->posY);
        w.items[i].type = items[i]->type;
    }

    // Lista de Oros
    w.num_golds = htons(num_golds);
    w.golds.resize(num_golds * sizeof(gold_t));

    for (i = 0; i < num_golds; i ++) {
        w.golds[i].pos_x = htons(golds[i]->posX);
        w.golds[i].pos_y = htons(golds[i]->posY);
        w.golds[i].quantity = golds[i]->quantity;
    }

    // Lista de Ataques
    w.num_attacks = htons(num_attacks);
    w.attacks.resize(num_attacks * sizeof(attack_t));

    for (i = 0; i < num_attacks; i ++) {
        w.attacks[i].pos_x = htons(attacks[i]->posX);
        w.attacks[i].pos_y = htons(attacks[i]->posY);
        w.attacks[i].orientation = attacks[i]->direction;
        w.attacks[i].type = attacks[i]->type;
        w.attacks[i].is_colliding = attacks[i]->isColliding;
    }

    // ------------------ //
    // Carga del byte_msg //
    // ------------------ //

    int pos = 0;
    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16 + message_length);

    // Longitud total mensaje
    memcpy(&byte_msg[pos], &w.length, SIZE_16);
    pos += SIZE_16;

    // Info particular del Player del cliente
    memcpy(&byte_msg[pos], &w.player_info.actual_mana, SIZE_16);
    pos += SIZE_16;
    memcpy(&byte_msg[pos], &w.player_info.max_mana, SIZE_16);
    pos += SIZE_16;
    memcpy(&byte_msg[pos], &w.player_info.actual_gold, SIZE_16);
    pos += SIZE_16;
    memcpy(&byte_msg[pos], &w.player_info.max_gold, SIZE_16);
    pos += SIZE_16;
    memcpy(&byte_msg[pos], &w.player_info.actual_experience, SIZE_32);
    pos += SIZE_32;

    // Inventario
    byte_msg[pos] = inventory_length;
    pos += SIZE_8;
    for (i = 0; i < inventory_length; i ++) {
        byte_msg[pos] = player.inventory.items[i]->type;
        pos += SIZE_8;
    }

    // Lista de Players
    memcpy(&byte_msg[pos], &w.num_players, SIZE_16);
    pos+=SIZE_16;
    for (i = 0; i < num_players; i ++) {
        memcpy(&byte_msg[pos], &w.players[i].id, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.players[i].pos_x, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.players[i].pos_y, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.players[i].actual_life, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.players[i].max_life, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.players[i].level, SIZE_16);
        pos += SIZE_16;
        byte_msg[pos] = w.players[i].is_alive;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].is_meditating;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].is_reviving;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].orientation;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].race_type;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].class_type;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].weapon;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].armor;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].helmet;
        pos += SIZE_8;
        byte_msg[pos] = w.players[i].shield;
        pos += SIZE_8;
    }

    // Lista de Criaturas
    memcpy(&byte_msg[pos], &w.num_creatures, SIZE_16);
    pos += SIZE_16;
    for (i = 0; i < num_creatures; i ++) {
        memcpy(&byte_msg[pos], &w.creatures[i].pos_x, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.creatures[i].pos_y, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.creatures[i].actual_life, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.creatures[i].max_life, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.creatures[i].level, SIZE_16);
        pos += SIZE_16;
        byte_msg[pos] = w.creatures[i].type;
        pos += SIZE_8;
        byte_msg[pos] = w.creatures[i].orientation;
        pos += SIZE_8;
    }

    // Lista de items
    memcpy(&byte_msg[pos], &w.num_items, SIZE_16);
    pos += SIZE_16;
    for (i = 0; i < num_items; i ++) {
        memcpy(&byte_msg[pos], &w.items[i].pos_x, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.items[i].pos_y, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.items[i].type, SIZE_8);
        pos += SIZE_8;
    }

    // Lista de oros
    memcpy(&byte_msg[pos], &w.num_golds, SIZE_16);
    pos += SIZE_16;
    for (i = 0; i < num_golds; i ++) {
        memcpy(&byte_msg[pos], &w.golds[i].pos_x, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.golds[i].pos_y, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.golds[i].quantity, SIZE_16);
        pos += SIZE_16;
    }

    // Lista de ataques
    memcpy(&byte_msg[pos], &w.num_attacks, SIZE_16);
    pos += SIZE_16;
    for (i = 0; i < num_attacks; i ++) {
        memcpy(&byte_msg[pos], &w.attacks[i].pos_x, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.attacks[i].pos_y, SIZE_16);
        pos += SIZE_16;
        memcpy(&byte_msg[pos], &w.attacks[i].orientation, SIZE_8);
        pos += SIZE_8;
        memcpy(&byte_msg[pos], &w.attacks[i].type, SIZE_8);
        pos += SIZE_8;
        memcpy(&byte_msg[pos], &w.attacks[i].is_colliding, SIZE_8);
        pos += SIZE_8;
    }

    socket.sendBytes(byte_msg.data(), byte_msg.size());

    if (debug) {
        std::cout << "Mundo enviado al player " << player.id << ":\n";
        for (char& c : byte_msg)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }
}

void ServerProtocol::sendItemsList(list_t& list) {
    int message_length = SIZE_8 + SIZE_16 + SIZE_16 +
            list.num_items * (SIZE_8 + SIZE_16);

    int pos = 0;

    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16 + message_length);

    memcpy(&byte_msg[pos], &list.show_price, SIZE_8);
    pos += SIZE_8;

    memcpy(&byte_msg[pos], &list.gold_quantity, SIZE_16);
    pos += SIZE_16;

    memcpy(&byte_msg[pos], &list.num_items, SIZE_16);
    pos += SIZE_16;

    int i;
    for (i = 0; i < ntohs(list.num_items); i ++) {
        memcpy(&byte_msg[pos], &list.items[i].type, SIZE_8);
        pos += SIZE_8;

        memcpy(&byte_msg[pos], &list.items[i].price, SIZE_16);
        pos += SIZE_16;
    }
}

void ServerProtocol::sendGameMessage(const std::string& message) {
    std::vector<char> byte_msg;
    std::vector<char> msg(message.begin(), message.end());
    byte_msg.resize(SIZE_8 + msg.size());

    byte_msg[0] = msg.size();
    memcpy(byte_msg.data() + SIZE_8, msg.data(), msg.size());

    socket.sendBytes(byte_msg.data(), byte_msg.size());
}
