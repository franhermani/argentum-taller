#ifndef THROW_COMMAND_H
#define THROW_COMMAND_H

#include "command.h"
#include "../player.h"

class ThrowCommand : public Command{
    Player& player;
    int itemType;

public:
    // Constructor
    ThrowCommand(Player& player, const int item_type);

    // Constructor y asignacion por copia deshabilitados
    ThrowCommand(const ThrowCommand&) = delete;
    ThrowCommand& operator=(const ThrowCommand&) = delete;

    // Destructor
    ~ThrowCommand() override;

    // Toma un objeto del inventario y lo tira al piso
    void execute() override;
};

#endif // THROW_COMMAND_H
