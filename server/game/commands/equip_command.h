#ifndef EQUIP_COMMAND_H
#define EQUIP_COMMAND_H

#include "command.h"
#include "../player.h"

class EquipCommand : public Command {
    Player& player;
    int itemType;

public:
    // Constructor
    EquipCommand(Player& player, const int item_type);

    // Constructor y asignacion por copia deshabilitados
    EquipCommand(const EquipCommand&) = delete;
    EquipCommand& operator=(const EquipCommand&) = delete;

    // Destructor
    ~EquipCommand() override;

    // Toma un objeto del inventario y lo equipa
    void execute() override;
};

#endif // EQUIP_COMMAND_H
