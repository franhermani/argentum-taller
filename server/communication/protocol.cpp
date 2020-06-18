#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <cstring>
#include "protocol.h"
#include "../../common/defines/commands.h"
//#include "../../common/commands/username_command.h"
//#include "../../common/commands/meditate_command.h"
//#include "../../common/commands/revive_command.h"
//#include "../../common/commands/heal_command.h"
//#include "../../common/commands/list_command.h"
//#include "../../common/commands/move_command.h"
//#include "../../common/commands/attack_command.h"

#define BYTE_SIZE 1

ServerProtocol::ServerProtocol(Socket& socket) : socket(socket) {}

// TODO: llamar a CommandFactory y devolver clase derivada de Command
Command* ServerProtocol::receiveCommand() {
    std::vector<char> arguments;
    char buffer1[BYTE_SIZE], buffer2[BYTE_SIZE];

    socket.receiveBytes(buffer1, BYTE_SIZE);
    socket.receiveBytes(buffer2, BYTE_SIZE);

    int type = buffer1[0];
    int length = buffer2[0];

    if (length > 0) {
        arguments.resize(length);
        socket.receiveBytes(arguments.data(), arguments.size());
    }

    if (type == CMD_USERNAME) {
        std::string username(arguments.begin(), arguments.end());
//        return new UsernameCommand(username);
    } else if (type == CMD_MEDITATE) {
//        return new MeditateCommand();
    } else if (type == CMD_REVIVE) {
        if (length > 0) {
            uint16_t priest_id;
            memcpy(&priest_id, arguments.data(), arguments.size());
//            return new ReviveCommand(ntohs(priest_id));
        } else {
//            return new ReviveCommand();
        }
    } else if (type == CMD_HEAL) {
        uint16_t priest_id;
        memcpy(&priest_id, arguments.data(), arguments.size());
//        return new HealCommand(ntohs(priest_id));
    } else if (type == CMD_DEPOSIT) {
        // TODO:...
    } else if (type == CMD_WITHDRAW) {
        // TODO:...
    } else if (type == CMD_LIST) {
        uint16_t npc_id;
        memcpy(&npc_id, arguments.data(), arguments.size());
//        return new ListCommand(ntohs(npc_id));
    } else if (type == CMD_BUY) {
        // TODO:...
    } else if (type == CMD_SELL) {
        // TODO:...
    } else if (type == CMD_TAKE) {
        // TODO:...
    } else if (type == CMD_THROW) {
        // TODO:...
    } else if (type == CMD_MESSAGE) {
        // TODO:...
    } else if (type == CMD_MOVE) {
//        int direction = arguments[0];
//        return new MoveCommand(direction);
    } else if (type == CMD_ATTACK) {
        uint16_t enemy_id;
        memcpy(&enemy_id, arguments.data(), arguments.size());
//        return new AttackCommand(ntohs(enemy_id));
    } else if (type == CMD_EQUIP) {
        // TODO:...
    } else if (type == CMD_TRICK) {
        // TODO:...
    }
    return nullptr;
}

void ServerProtocol::sendWorldAround(WorldMonitor& world_monitor,
        Player& player) {
    std::vector<std::vector<Terrain>> matrix =
            world_monitor.getMatrixAround(player);
    std::vector<Player*> players =
            world_monitor.getPlayersAround(player);

    // TODO: ...
//    std::vector<NPC*> npc = world.getNPCsAround(player);
//    std::vector<Item*> items = world.getItemsAround(player);

//    std::vector<char> byte_msg = ...;
//    socket.sendBytes(byte_msg.data(), byte_msg.size());
}
