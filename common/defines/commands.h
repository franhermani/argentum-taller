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
    CMD_STOP_MOVE,
    CMD_ATTACK,
    CMD_EQUIP,
    CMD_UNEQUIP
};

// Move Command
enum moveDirection {
    LEFT,
    RIGHT,
    DOWN,
    UP,
};

// Take Command
enum takeType {
    TAKE_ITEM,
    TAKE_GOLD
};

// Unequip Command
enum unequipType {
    UNEQUIP_WEAPON,
    UNEQUIP_ARMOR,
    UNEQUIP_HELMET,
    UNEQUIP_SHIELD
};

#endif // COMMANDS_H
