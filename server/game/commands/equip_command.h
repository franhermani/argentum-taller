#ifndef EQUIP_COMMAND_H
#define EQUIP_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

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

    // Toma un item del inventario y lo equipa
    void execute(World& world) override;
};

#endif // EQUIP_COMMAND_H
