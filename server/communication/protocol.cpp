#include <string>
#include <vector>
#include "protocol.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/items.h"
#include "../../common/defines/messages.h"
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

    if (debug)
        std::cout << "Recibido el comando tipo " << type <<
                  " de longitud " << length << "\n";

    if (length > 0) {
        arguments.resize(length);
        socket.receiveBytes(arguments.data(), arguments.size());
    }
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

    matrix_t m;
    m.length = htons(2 * SIZE_16 + matrix_length * SIZE_8);
    m.width = htons(width);
    m.height = htons(height);

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

    int num_npcs = npcs.size();

    npcs_t n;

    // Longitud total del mensaje
    uint16_t message_length = SIZE_16 + num_npcs * (2 * SIZE_16 + 2 * SIZE_8);
    n.length = htons(message_length);

    // Cantidad de NPCs
    // TODO: si hago htons(num_npcs) lo carga en 0...
    n.num_npcs = num_npcs;
    n.npcs.resize(num_npcs * sizeof(npc_t));

    // Lista de NPCs
    int i;
    for (i = 0; i < num_npcs; i ++) {
        n.npcs[i].type = npcs[i]->type;
        n.npcs[i].pos_x = htons(npcs[i]->posX);
        n.npcs[i].pos_y = htons(npcs[i]->posY);
        n.npcs[i].orientation = npcs[i]->orientation;
    }

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
    std::vector<Player*> players = world_monitor.
            getPlayersAround(player);
    std::vector<Creature*> creatures = world_monitor.
            getCreaturesAround(player);
    std::vector<Item*> items = world_monitor.
            getItemsAround(player);

    // Longitudes variables
    uint8_t inventory_length = player.inventory.numItems;
    uint16_t num_players = players.size();
    uint16_t num_creatures = creatures.size();
//    int num_items = items.size();

    // Longitud total del mensaje
    // TODO: completar con criaturas e items
    size_t message_length =
            4 * SIZE_16 + SIZE_32 + SIZE_8 +
            SIZE_8 + inventory_length * SIZE_8 +
            SIZE_16 + num_players * (6 * SIZE_16 + 9 * SIZE_8) +
            SIZE_16 + num_creatures * (6*SIZE_16 + 2 * SIZE_8);

    // ------------------------ //
    // Carga del struct world_t //
    // ------------------------ //

    // Longitud total mensaje
    w.length = htons(message_length);

    // Info particular del player del cliente
    w.player_info.actual_mana = htons(player.actualMana);
    w.player_info.max_mana = htons(player.maxMana);
    w.player_info.actual_gold = htons(player.actualGold);
    w.player_info.max_gold = htons(player.maxGold);
    w.player_info.actual_experience = htonl(player.actualExperience);
    w.player_info.long_distance = player.weapon &&
            player.weapon->isLongDistance() ? 1 : 0;

    // Info generica de todos los players (incluido el del cliente)
    // TODO: si hago htons(num_players) lo carga en 0...
    w.num_players = num_players;
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

    w.num_creatures = num_creatures;
    w.creatures.resize(num_creatures * sizeof(creature_t));
    for (i = 0; i < num_creatures; i ++) {
        w.creatures[i].id = htons(creatures[i]->id);
        w.creatures[i].pos_x = htons(creatures[i]->posX);
        w.creatures[i].pos_y = htons(creatures[i]->posY);
        w.creatures[i].actual_life = htons(creatures[i]->actualLife);
        w.creatures[i].max_life = htons(creatures[i]->maxLife);
        w.creatures[i].level = htons(creatures[i]->level);
        w.creatures[i].type = creatures[i]->type;
        w.creatures[i].orientation = creatures[i]->orientation;
    }



    // ------------------ //
    // Carga del byte_msg //
    // ------------------ //

    int pos = 0;
    std::vector<char> byte_msg;
    byte_msg.resize(SIZE_16 + message_length);

    // Longitud total mensaje
    memcpy(&byte_msg[pos], &w.length, SIZE_16);

    // Info particular del player del cliente
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.actual_mana, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.max_mana, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.actual_gold, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.max_gold, SIZE_16);
    memcpy(&byte_msg[pos+=SIZE_16], &w.player_info.actual_experience, SIZE_32);
    memcpy(&byte_msg[pos+=SIZE_32], &w.player_info.long_distance, SIZE_8);

    // Inventario
    byte_msg[pos+=SIZE_8] = inventory_length;
    for (i = 0; i < inventory_length; i ++)
        byte_msg[pos+=SIZE_8] = player.inventory.items[i]->type;

    // Lista de players
    memcpy(&byte_msg[pos+=SIZE_16], &w.num_players, SIZE_16);
    pos -= SIZE_8;
    for (i = 0; i < num_players; i ++) {
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].id, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].pos_x, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].pos_y, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].actual_life, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].max_life, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.players[i].level, SIZE_16);
        byte_msg[pos+=SIZE_16] = w.players[i].is_alive;
        byte_msg[pos+=SIZE_8] = w.players[i].is_meditating;
        byte_msg[pos+=SIZE_8] = w.players[i].orientation;
        byte_msg[pos+=SIZE_8] = w.players[i].race_type;
        byte_msg[pos+=SIZE_8] = w.players[i].class_type;
        byte_msg[pos+=SIZE_8] = w.players[i].weapon;
        byte_msg[pos+=SIZE_8] = w.players[i].armor;
        byte_msg[pos+=SIZE_8] = w.players[i].helmet;
        byte_msg[pos+=SIZE_8] = w.players[i].shield;
    }

    // Lista de criaturas
    memcpy(&byte_msg[pos+=SIZE_16], &w.num_creatures, SIZE_16);
    pos -= SIZE_8;
    for (i = 0; i < num_creatures; i ++) {
        memcpy(&byte_msg[pos+=SIZE_16], &w.creatures[i].id, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.creatures[i].pos_x, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.creatures[i].pos_y, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.creatures[i].actual_life, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.creatures[i].max_life, SIZE_16);
        memcpy(&byte_msg[pos+=SIZE_16], &w.creatures[i].level, SIZE_16);
        byte_msg[pos+=SIZE_16] = w.creatures[i].type;
        byte_msg[pos+=SIZE_8] = w.creatures[i].orientation;
        pos -= SIZE_8;
    }

    // Lista de items
    // TODO: ...

    // Lista de ataques (no incluye ataques cuerpo a cuerpo)
    // TODO: usar el bool isLongDistance()

    socket.sendBytes(byte_msg.data(), byte_msg.size());

    if (debug) {
        std::cout << "Mundo enviado al player " << player.id << ":\n";
        for (char& c : byte_msg)
            printf("%02X ", (unsigned) (unsigned char) c);
        std::cout << "\n";
    }
}

void ServerProtocol::sendItemsList(WorldMonitor &world_monitor,
        Player &player) {
    // TODO:
    // - Enviar 1 byte con la cantidad de items
    // - Enviar N structs listed_item_t
}

void ServerProtocol::sendGameMessage(const std::string& message,
        Player &player) {
    std::vector<char> byte_msg;
    std::vector<char> msg(message.begin(), message.end());
    byte_msg.resize(SIZE_8 + msg.size());

    byte_msg[0] = msg.size();
    memcpy(byte_msg.data() + SIZE_8, msg.data(), msg.size());

    socket.sendBytes(byte_msg.data(), byte_msg.size());
}
