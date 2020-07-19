
#ifndef ARGENTUM_COMMAND_DTO_FACTORY_H
#define ARGENTUM_COMMAND_DTO_FACTORY_H

#include <SDL2/SDL_events.h>
#include "command_dto.h"
#include "../../common/defines/commands.h"
#include "../game/exception.h"
#include "../game/map_monitor.h"
#include "../game/game_render.h"



class CommandDTOFactory {
    MapMonitor &mapMonitor;
    GameRender *gameRender;
public:
    // Constructor
    CommandDTOFactory(MapMonitor &mapMonitor, GameRender* gameRender);


    // Destrutor
    ~CommandDTOFactory();

    // Constructor y asignacion por copia deshabilitados
    CommandDTOFactory(const CommandDTOFactory& other) = delete;
    CommandDTOFactory& operator=(const CommandDTOFactory& other) = delete;

    // Recibe un evento ingresado por input
    CommandDTO* operator()(int key);


    int isLeftClick(SDL_Event &event);
    int isMoveKey(SDL_Event& event);
    void waitForLeftClick(int &x, int &y);

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
};


#endif //ARGENTUM_COMMAND_DTO_FACTORY_H
