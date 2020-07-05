#include <string>
#include <cstring>
#include <cstdint>
#include <arpa/inet.h>
#include "command_factory.h"
#include "../../../common/defines/commands.h"
#include "meditate_command.h"
#include "revive_command.h"
#include "heal_command.h"
#include "deposit_item_command.h"
#include "list_command.h"
#include "take_command.h"
#include "throw_command.h"
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
            uint16_t pos_x, pos_y;
            memcpy(&pos_x, arguments.data(), SIZE_16);
            memcpy(&pos_y, arguments.data() + SIZE_16, SIZE_16);
            return new ReviveCommand(player, ntohs(pos_x), ntohs(pos_y));
        } else {
            return new ReviveCommand(player);
        }

    } else if (type == CMD_HEAL) {
        uint16_t pos_x, pos_y;
        memcpy(&pos_x, arguments.data(), SIZE_16);
        memcpy(&pos_y, arguments.data() + SIZE_16, SIZE_16);
        return new HealCommand(player, ntohs(pos_x), ntohs(pos_y));

    } else if (type == CMD_DEPOSIT_ITEM) {
        uint8_t item_type;
        uint16_t pos_x, pos_y;
        memcpy(&item_type, arguments.data(), SIZE_8);
        memcpy(&pos_x, arguments.data() + SIZE_8, SIZE_16);
        memcpy(&pos_y, arguments.data() + SIZE_8 + SIZE_16, SIZE_16);
        return new DepositItemCommand(player, item_type,
                ntohs(pos_x), ntohs(pos_y));

    } else if (type == CMD_WITHDRAW_ITEM) {
        // TODO:...

    } else if (type == CMD_DEPOSIT_GOLD) {
        // TODO:...

    } else if (type == CMD_WITHDRAW_GOLD) {
        // TODO:...

    } else if (type == CMD_LIST) {
        uint16_t pos_x, pos_y;
        memcpy(&pos_x, arguments.data(), SIZE_16);
        memcpy(&pos_y, arguments.data() + SIZE_16, SIZE_16);
        return new ListCommand(player, ntohs(pos_x), ntohs(pos_y));

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
        int item_type = arguments[0];
        return new ThrowCommand(player, item_type);

    } else if (type == CMD_MOVE) {
        int direction = arguments[0];
        return new MoveCommand(player, direction);

    } else if (type == CMD_ATTACK) {
        return new AttackCommand(player);

    } else if (type == CMD_EQUIP) {
        int item_type = arguments[0];
        return new EquipCommand(player, item_type);
    }
    return nullptr;
}
