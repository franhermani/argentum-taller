#include "command_dto_manager.h"
#include "../data_transfer_objects/move_command_dto.h"
#include "../data_transfer_objects/heal_command_dto.h"
#include "../data_transfer_objects/take_command_dto.h"
#include "../data_transfer_objects/list_command_dto.h"
#include "../data_transfer_objects/equip_command_dto.h"
#include "../data_transfer_objects/unequip_command_dto.h"
#include "../data_transfer_objects/throw_command_dto.h"
#include "../data_transfer_objects/revive_command_dto.h"
#include "../data_transfer_objects/meditate_command_dto.h"
#include "../data_transfer_objects/withdraw_gold_command_dto.h"
#include "../data_transfer_objects/withdraw_item_command_dto.h"
#include "../data_transfer_objects/deposit_gold_command_dto.h"
#include "../data_transfer_objects/deposit_item_command_dto.h"
#include "../data_transfer_objects/attack_command_dto.h"
#include "../data_transfer_objects/sell_item_command_dto.h"
#include "../data_transfer_objects/buy_item_command_dto.h"
#include "game_input_handler.h"
#include <vector>



CommandDTOManager::CommandDTOManager(ClientWorldMonitor &worldMonitor,
        GameRender* gameRender, GameInputHandler& inputHandler)
        : worldMonitor(worldMonitor), gameRender(gameRender),
          inputHandler(inputHandler){}

CommandDTOManager::~CommandDTOManager() {}

CommandDTO* CommandDTOManager::operator()(int key) {
    if (key == SDLK_LEFT) {
        return handleMove(LEFT);
    } else if (key == SDLK_RIGHT) {
        return handleMove(RIGHT);
    } else if (key == SDLK_UP) {
        return handleMove(UP);
    } else if (key == SDLK_DOWN) {
        return handleMove(DOWN);
    } else if (key == SDLK_F12) {
        gameRender->toggleFullscreen();
        throw CommandCreationException("Tecla ingresada no crea comando");
    } else if (key == SDLK_F11) {
        gameRender->toggleMusic();
        throw CommandCreationException("Tecla ingresada no crea comando");
    } else if (key == SDLK_F10) {
        gameRender->toggleSound();
        throw CommandCreationException("Tecla ingresada no crea comando");
    } else if (key == SDLK_ESCAPE) {
        throw StopGameException("Han solicitado salir del juego");
    } else if (worldMonitor.isInteracting()) {
        if (key == SDLK_w) {
            return handleWithdraw();
        } else if (key == SDLK_b) {
            return handleBuy();
        } else if (key == SDLK_s) {
            return handleSell();
        } else if (key == SDLK_d) {
            return handleDeposit();
        } else {
            throw CommandCreationException("Tecla ingresada no crea comando");
        }
    } else {
        if (key == SDLK_a) {
            return handleAttack();
        } else if (key == SDLK_h) {
            return handleHeal();
        } else if (key == SDLK_l) {
            return handleList();
        } else if (key == SDLK_m) {
            return handleMeditate();
        } else if (key == SDLK_r) {
            return handleRevive();
        } else if (key == SDLK_t) {
            return handleTake();
        } else if (key == SDLK_y) {
            return handleThrow();
        } else if (key == SDLK_e) {
            return handleEquip();
        } else if (key == SDLK_u) {
            return handleUnequip();
        } else {
            throw CommandCreationException("Tecla ingresada no crea comando");
        }
    }
}


CommandDTO* CommandDTOManager::handleMove(moveDirection direction){
    worldMonitor.uninteract();
    return new MoveCommandDTO(direction);
}

CommandDTO* CommandDTOManager::handleBuy() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    std::vector<int> npc_pos = worldMonitor.getNpcLookingAt();
    if (gameRender->isClickingListItems(x, y)) {
        return new BuyItemCommandDTO(gameRender->
                getListItemByPosition(x, y), npc_pos[0], npc_pos[1]);
    } else {
        throw CommandCreationException(
                "No se dieron las condiciones "
                "para la creacion del comando Buy");
    }
}

CommandDTO* CommandDTOManager::handleAttack() {
    return new AttackCommandDTO();
}
CommandDTO* CommandDTOManager::handleMeditate() {
    return new MeditateCommandDTO();
}

CommandDTO* CommandDTOManager::handleSell() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    std::vector<int> npc_pos = worldMonitor.getNpcLookingAt();
    if (gameRender->isClickingInventoryItems(x, y))
        return new SellItemCommandDTO(
                gameRender->getInventoryItemByPosition(x, y),
                npc_pos[0], npc_pos[1]);
    else
        throw CommandCreationException(
                "No se cumplen las "
                "condiciones para la creacion del comando Sell");
}

CommandDTO* CommandDTOManager::handleWithdraw() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    std::vector<int> npc_pos = worldMonitor.getNpcLookingAt();
    if (gameRender->isClickingListItems(x, y))
        return new WithdrawItemCommandDTO(gameRender->
                getListItemByPosition(x, y), npc_pos[0], npc_pos[1]);
    else if (gameRender->isClickingListGold(x, y))
        return new WithdrawGoldCommandDTO(npc_pos[0], npc_pos[1]);
    else
        throw CommandCreationException(
                "No se cumplen las condiciones para "
                "la creacion del comando withdraw");
}

CommandDTO* CommandDTOManager::handleDeposit() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    std::vector<int> npc_pos = worldMonitor.getNpcLookingAt();
    if (gameRender->isClickingInventoryItems(x, y))
        return new DepositItemCommandDTO(gameRender->
                getInventoryItemByPosition(x, y), npc_pos[0], npc_pos[1]);
    else if (gameRender->isClickingInventoryGold(x, y))
        return new DepositGoldCommandDTO(npc_pos[0], npc_pos[1]);
    else
        throw CommandCreationException(
                "No se cumplen las condiciones para la "
                "creacion del comando deposit");
}

CommandDTO* CommandDTOManager::handleRevive() {
    try {
        std::vector<int> priest_position =
                worldMonitor.getPriestLookingAt();
        return new ReviveCommandDTO(priest_position[0],
                                    priest_position[1]);
    } catch (MapException& e) {
        return new ReviveCommandDTO();
    }
}

CommandDTO* CommandDTOManager::handleThrow() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    return new ThrowCommandDTO(
            gameRender->getInventoryItemByPosition(x, y));
}

CommandDTO* CommandDTOManager::handleTake() {
    try {
        std::vector<int> item_pos = worldMonitor.getItemStandingAt();
        return new TakeCommandDTO(TAKE_ITEM, item_pos[0], item_pos[1]);
    } catch (MapException& e) {
        //si hay excepcion en getgold standing at, no la catcheamos
        //porque queremos que la catchee la funcion que llama a esta
        std::vector<int> gold_pos = worldMonitor.getGoldStandingAt();
        return new TakeCommandDTO(TAKE_GOLD, gold_pos[0], gold_pos[1]);
    }
}

CommandDTO* CommandDTOManager::handleList() {
    std::vector<int> npc_position =
            worldMonitor.getNpcLookingAt();
    worldMonitor.interact();
    return new ListCommandDTO(npc_position[0], npc_position[1]);
}
CommandDTO* CommandDTOManager::handleHeal() {
    std::vector<int> priest_position =
            worldMonitor.getPriestLookingAt();
    return new HealCommandDTO(priest_position[0],
                              priest_position[1]);
}

CommandDTO* CommandDTOManager::handleEquip() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    return new EquipCommandDTO(
            gameRender->getInventoryItemByPosition(x, y));
}

CommandDTO* CommandDTOManager::handleUnequip() {
    int x,y;
    inputHandler.waitForLeftClick(x, y);
    return new UnequipCommandDTO(
            gameRender->getEquippedTypeByPosition(x, y));
}



