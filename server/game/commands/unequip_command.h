#ifndef UNEQUIP_COMMAND_H
#define UNEQUIP_COMMAND_H

#include "command.h"
#include "../entities/living_beings/player.h"

class UnequipCommand : public Command {
    Player& player;
    int unequipType;

public:
    // Constructor
    UnequipCommand(Player& player, const int unequip_type);

    // Constructor y asignacion por copia deshabilitados
    UnequipCommand(const UnequipCommand&) = delete;
    UnequipCommand& operator=(const UnequipCommand&) = delete;

    // Destructor
    ~UnequipCommand() override;

    // Toma un item equipado y lo guarda en el inventario
    void execute(World& world) override;
};


#endif // UNEQUIP_COMMAND_H
