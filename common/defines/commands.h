#ifndef COMMANDS_H
#define COMMANDS_H

// All Commands
enum commandType {
    CMD_MEDITATE,
    CMD_REVIVE,
    CMD_HEAL,
    CMD_DEPOSIT,
    CMD_WITHDRAW,
    CMD_LIST,
    CMD_BUY,
    CMD_SELL,
    CMD_TAKE,
    CMD_THROW,
    CMD_MESSAGE,
    CMD_MOVE,
    CMD_ATTACK,
    CMD_EQUIP,
    CMD_TRICK
};

// Move Command
enum moveDirection {
    LEFT,
    RIGHT,
    DOWN,
    UP,
};

#endif // COMMANDS_H
