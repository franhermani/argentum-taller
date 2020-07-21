
#ifndef ARGENTUM_COMMAND_DTO_MANAGER_H
#define ARGENTUM_COMMAND_DTO_MANAGER_H

#include <SDL2/SDL_events.h>
#include "../data_transfer_objects/command_dto.h"
#include "../../common/defines/commands.h"
#include "exception.h"
#include "client_world_monitor.h"
#include "game_render.h"

class GameInputHandler;

class CommandDTOManager {
    ClientWorldMonitor &mapMonitor;
    GameRender *gameRender;
    GameInputHandler &inputHandler;


    // Funciones internas para manejo y creacion de cada tipo de comando
    CommandDTO* handleEquip();
    CommandDTO* handleUnequip();
    CommandDTO* handleHeal();
    CommandDTO* handleList();
    CommandDTO* handleTake();
    CommandDTO* handleThrow();
    CommandDTO* handleRevive();
    CommandDTO* handleDeposit();
    CommandDTO* handleSell();
    CommandDTO* handleWithdraw();
    CommandDTO* handleBuy();
    CommandDTO* handleAttack();
    CommandDTO* handleMeditate();
    CommandDTO* handleMove(moveDirection direction);

public:
    // Constructor
    CommandDTOManager(ClientWorldMonitor &mapMonitor, GameRender* gameRender,
                      GameInputHandler& inputHandler);

    // Destrutor
    ~CommandDTOManager();

    // Constructor y asignacion por copia deshabilitados
    CommandDTOManager(const CommandDTOManager& other) = delete;
    CommandDTOManager& operator=(const CommandDTOManager& other) = delete;

    // Recibe un evento ingresado por input
    CommandDTO* operator()(int key);

};


#endif //ARGENTUM_COMMAND_DTO_MANAGER_H
