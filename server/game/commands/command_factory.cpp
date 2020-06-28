#include <string>
#include <cstring>
#include <cstdint>
#include <arpa/inet.h>
#include "command_factory.h"
#include "../../../common/defines/commands.h"
#include "meditate_command.h"
#include "revive_command.h"
#include "heal_command.h"
#include "list_command.h"
#include "take_command.h"
#include "move_command.h"
#include "attack_command.h"
#include "equip_command.h"

#define SIZE_8      sizeof(uint8_t)
#define SIZE_16     sizeof(uint16_t)

CommandFactory::CommandFactory() = default;

Command* CommandFactory::operator()(Player& player, int type,
        std::vector<char>& arguments) {
    if (type == CMD_MEDITATE) {
        return new MeditateCommand(player);

    } else if (type == CMD_REVIVE) {
        if (! arguments.empty()) {
            uint16_t priest_id;
            memcpy(&priest_id, arguments.data(), arguments.size());
            return new ReviveCommand(player, ntohs(priest_id));
        } else {
            return new ReviveCommand(player);
        }

    } else if (type == CMD_HEAL) {
        uint16_t priest_id;
        memcpy(&priest_id, arguments.data(), arguments.size());
        return new HealCommand(player, ntohs(priest_id));

    } else if (type == CMD_DEPOSIT) {
        // TODO:...

    } else if (type == CMD_WITHDRAW) {
        // TODO:...

    } else if (type == CMD_DEPOSIT_GOLD) {
        // TODO:...

    } else if (type == CMD_WITHDRAW_GOLD) {
        // TODO:...

    } else if (type == CMD_LIST) {
        uint16_t npc_id;
        memcpy(&npc_id, arguments.data(), arguments.size());
        return new ListCommand(player, ntohs(npc_id));

    } else if (type == CMD_BUY) {
        // TODO:...

    } else if (type == CMD_SELL) {
        // TODO:...

    } else if (type == CMD_TAKE) {
        uint16_t pos_x, pos_y;
        memcpy(&pos_x, arguments.data(), SIZE_16);
        memcpy(&pos_y, arguments.data() + SIZE_16, SIZE_16);
        return new TakeCommand(player, ntohs(pos_x), ntohs(pos_y));

    } else if (type == CMD_THROW) {
        // TODO:...

    } else if (type == CMD_MOVE) {
        int direction = arguments[0];
        return new MoveCommand(player, direction);

    } else if (type == CMD_ATTACK) {
        uint8_t enemy_id_type = arguments[0];
        uint16_t enemy_id;
        memcpy(&enemy_id, arguments.data() + SIZE_8,
                arguments.size() - SIZE_8);
        return new AttackCommand(player, enemy_id_type, ntohs(enemy_id));

    } else if (type == CMD_EQUIP) {
        int item_type = arguments[0];
        return new EquipCommand(player, item_type);

    } else if (type == CMD_TRICK) {
        // TODO:...
    }
    return nullptr;
}
