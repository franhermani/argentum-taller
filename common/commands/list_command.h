#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include <vector>
#include "command.h"

class ListCommand : public Command {
    uint16_t npcId;

public:
    // Constructor
    explicit ListCommand(const uint16_t npc_id);

    // Constructor y asignacion por copia deshabilitados
    ListCommand(const ListCommand&) = delete;
    ListCommand& operator=(const ListCommand&) = delete;

    // Destructor
    ~ListCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Lista los objetos del comerciante o banquero segun su 'npcId'
    void execute(Player& player) override;
};


#endif // LIST_COMMAND_H
