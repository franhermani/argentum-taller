#ifndef COMMANDS_H
#define COMMANDS_H

// All Commands
enum commandType {
    CMD_MEDITATE,
    CMD_REVIVE,
    CMD_HEAL,
    CMD_DEPOSIT_ITEM,
    CMD_WITHDRAW_ITEM,
    CMD_DEPOSIT_GOLD,
    CMD_WITHDRAW_GOLD,
    CMD_LIST,
    CMD_BUY,
    CMD_SELL,
    CMD_TAKE,
    CMD_THROW,
    CMD_MOVE,
    CMD_ATTACK,
    CMD_EQUIP
};

// Move Command
enum moveDirection {
    LEFT,
    RIGHT,
    DOWN,
    UP,
};

#endif // COMMANDS_H
