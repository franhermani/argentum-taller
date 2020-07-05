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
#include "exception.h"
#include <vector>

GameInputHandler::GameInputHandler(BlockingQueue<CommandDTO*>& commandQueue,
            MapMonitor& mapMonitor, GameRender* gameRender):
commandQueue(commandQueue), mapMonitor(mapMonitor), gameRender(gameRender) {}

GameInputHandler::~GameInputHandler() = default;

void GameInputHandler::play() {
    try {
        bool running = true;
        bool interacting_with_npc = true;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            CommandDTO *command;
            if (event.type == SDL_KEYDOWN) {
                auto &keyEvent = (SDL_KeyboardEvent &) event;
                int key = keyEvent.keysym.sym;
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
                } else if (key == SDLK_a){
                    command = new AttackCommandDTO();
                } else if (key == SDLK_h) {
                    std::vector<int> priest_position =
                            mapMonitor.getPriestLookingAt();
                    if (priest_position[0] == -1) continue;
                    command = new HealCommandDTO(priest_position[0],
                            priest_position[1]);
                } else if (key == SDLK_l) {
                    try {
                        std::vector<int> npc_position =
                                mapMonitor.getNpcLookingAt();
                        command = new ListCommandDTO(npc_position[0], npc_position[1]);
                    } catch (MapException& e) {
                        continue;
                    }
                } else if (key == SDLK_m) {
                    command = new MeditateCommandDTO();
                } else if (key == SDLK_r) {
                    std::vector<int> priest_position =
                            mapMonitor.getPriestLookingAt();
                    if (priest_position[0] == -1) {
                        command = new ReviveCommandDTO();
                    } else {
                        command = new ReviveCommandDTO(priest_position[0],
                            priest_position[1]);}
                } else if (key == SDLK_t) {
                    //TODO cuando tengamos los items guardados pedirlo al mapa
                    continue;
                    //command = new TakeCommandDTO(0, 0);
                } else if (key == SDLK_e) {
                    //TODO  Cuando pueda mostrar inventario esto va a ser equip
                    continue;
                } else {
                    continue;
                }
                commandQueue.push(command);
            } else if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (not interacting_with_npc) {
                    try {
                        command = new EquipCommandDTO(
                                gameRender->getInventoryItemByPosition(x, y));
                    } catch (ItemException &e) {
                        continue;
                    }
                } else {
                    //Chequeamos si estamos frente a un npc
                    try {
                        mapMonitor.getNpcLookingAt();
                    } catch (MapException& e) {
                        continue;
                    }
                    try {
                        command = new WithdrawItemCommandDTO(gameRender->getListItemByPosition(x, y), x, y);
                    } catch (ItemException &e) {
                        continue;
                    }
                    try {
                        command = new WithdrawGoldCommandDTO(
                                gameRender->getListItemByPosition(x, y), x, y);
                    } catch (ItemException &e) {
                        continue;
                    }
                    try {
                        command = new DepositItemCommandDTO(
                                gameRender->getInventoryItemByPosition(x, y), x, y);
                    } catch (ItemException &e) {
                        continue;
                    }
                    try {
                        command = new DepositGoldCommandDTO(
                                gameRender->getListItemByPosition(x, y), x, y);
                    } catch (ItemException &e) {
                        continue;
                    }
                }
                commandQueue.push(command);


            } else if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYUP) {
                continue;
            } else {
                continue;
            }
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
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
