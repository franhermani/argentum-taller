#include <iostream>
#include "game_input_handler.h"
#include "map_monitor.h"
#include "../data_transfer_objects/move_command_dto.h"
#include "../data_transfer_objects/heal_command_dto.h"
#include "../data_transfer_objects/take_command_dto.h"
#include "../data_transfer_objects/list_command_dto.h"
#include "../data_transfer_objects/equip_command_dto.h"
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
#include "exception.h"
#include <vector>

GameInputHandler::GameInputHandler(BlockingQueue<CommandDTO*>& commandQueue,
            MapMonitor& mapMonitor, GameRender* gameRender):
commandQueue(commandQueue), mapMonitor(mapMonitor), gameRender(gameRender) {}

GameInputHandler::~GameInputHandler() = default;

void GameInputHandler::play() {
    try {
        bool running = true;
        //bool interacting_with_npc = true;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            CommandDTO *command;
            if (event.type == SDL_KEYDOWN) {
                auto &keyEvent = (SDL_KeyboardEvent &) event;
                int key = keyEvent.keysym.sym;
                try {
                    if (key == SDLK_LEFT) {
                        command = new MoveCommandDTO(LEFT);
                    } else if (key == SDLK_RIGHT) {
                        command = new MoveCommandDTO(RIGHT);
                    } else if (key == SDLK_UP) {
                        command = new MoveCommandDTO(UP);
                    } else if (key == SDLK_DOWN) {
                        command = new MoveCommandDTO(DOWN);
                    } else if (key == SDLK_ESCAPE) {
                        running = false;
                        continue;
                    } else if (key == SDLK_a) {
                        command = new AttackCommandDTO();
                    } else if (key == SDLK_h) {
                        command = handleHeal();
                    } else if (key == SDLK_l) {
                        command = handleList();
                    } else if (key == SDLK_m) {
                        command = new MeditateCommandDTO();
                    } else if (key == SDLK_r) {
                        command = handleRevive();
                    } else if (key == SDLK_t) {
                        command = handleTake();
                    } else if (key == SDLK_y) {
                        command = handleThrow();
                    } else if (key == SDLK_e) {
                        command = handleEquip();
                    } else if (key == SDLK_d) {
                        command = handleDeposit();
                    } else if (key == SDLK_w) {
                        command = handleWithdraw();
                    } else if (key == SDLK_s) {
                        command = handleSell();
                    } else if (key == SDLK_b) {
                        command = handleBuy();
                    } else {
                        continue;
                    }
                    std::cout << "\n\n\n estoy pusheando comando "<< (int) command->serialize()[0];

                    commandQueue.push(command);
                }
                catch (ItemException& e) {
                    continue;
                } catch (MapException& e) {
                    continue;
                } catch(CommandCreationException& e) {
                    continue;
                }
            } else if (event.type == SDL_QUIT) {
                running = false;
            } else {
                continue;
            }
        }

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

CommandDTO* GameInputHandler::handleBuy() {
    int x,y;
    waitForLeftClick(x, y);
    std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
    if (gameRender->isClickingListItems(x, y))
        return new BuyItemCommandDTO(gameRender->getListItemByPosition(x, y), npc_pos[0], npc_pos[1]);
    else throw CommandCreationException(
                "No se dieron las condiciones para la creacion del comando Buy");
}

CommandDTO* GameInputHandler::handleSell() {
    int x,y;
    waitForLeftClick(x, y);
    std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
    if (gameRender->isClickingInventoryItems(x, y))
        return new SellItemCommandDTO(gameRender->getInventoryItemByPosition(x, y),
                npc_pos[0], npc_pos[1]);
    else throw CommandCreationException(
                "No se dieron las condiciones para la creacion del comando Sell");
}

CommandDTO* GameInputHandler::handleWithdraw() {
    int x,y;
    waitForLeftClick(x, y);
    std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
    if (gameRender->isClickingListItems(x, y))
        return new WithdrawItemCommandDTO(gameRender->
            getListItemByPosition(x, y), npc_pos[0], npc_pos[1]);
    else if (gameRender->isClickingListGold(x, y))
        return new WithdrawGoldCommandDTO(1, npc_pos[0], npc_pos[1]);
    else throw CommandCreationException(
            "No se dieron las condiciones para la creacion del comando withdraw");
}

CommandDTO* GameInputHandler::handleDeposit() {
    int x,y;
    waitForLeftClick(x, y);
    std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
    if (gameRender->isClickingInventoryItems(x, y))
        return new DepositItemCommandDTO(gameRender->
        getInventoryItemByPosition(x, y), npc_pos[0], npc_pos[1]);
    else if (gameRender->isClickingInventoryGold(x, y))
        return new DepositGoldCommandDTO(1, npc_pos[0], npc_pos[1]);
    else throw CommandCreationException(
            "No se dieron las condiciones para la creacion del comando deposit");
}

CommandDTO* GameInputHandler::handleRevive() {
    try {
        std::vector<int> priest_position =
                mapMonitor.getPriestLookingAt();
        return new ReviveCommandDTO(priest_position[0],
                                    priest_position[1]);
    } catch (MapException& e) {
        return new ReviveCommandDTO();
    }
}

CommandDTO* GameInputHandler::handleThrow() {
    int x,y;
    waitForLeftClick(x, y);
    return new ThrowCommandDTO(
            gameRender->getInventoryItemByPosition(x, y));
}

CommandDTO* GameInputHandler::handleTake() {
    std::vector<int> item_pos = mapMonitor.getItemLookingAt();
    return new TakeCommandDTO(0, item_pos[0], item_pos[1]);
}

CommandDTO* GameInputHandler::handleList() {
    std::vector<int> npc_position =
            mapMonitor.getNpcLookingAt();
    return new ListCommandDTO(npc_position[0], npc_position[1]);
}
CommandDTO* GameInputHandler::handleHeal() {
    std::vector<int> priest_position =
            mapMonitor.getPriestLookingAt();
    return new HealCommandDTO(priest_position[0],
                                 priest_position[1]);
}

CommandDTO* GameInputHandler::handleEquip() {
    int x,y;
    waitForLeftClick(x, y);
    return new EquipCommandDTO(
            gameRender->getInventoryItemByPosition(x, y));
}

void GameInputHandler::waitForLeftClick(int& x, int& y) {
    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        if (isLeftClick(event)) {
            SDL_GetMouseState(&x, &y);
            return;
        }
    }
}

int GameInputHandler::isLeftClick(SDL_Event& event) {
    return ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT));
}

void GameInputHandler::run() {
    play();
}

void GameInputHandler::stop() {
    keepRunning = false;
}

bool GameInputHandler::isDead() {
    return (! isRunning);
}
