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
            int x, y;
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
                        } catch (MapException &e) {
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
                                                           priest_position[1]);
                        }
                    } else if (key == SDLK_t) {
                        std::vector<int> item_pos = mapMonitor.getItemLookingAt();
                        new TakeCommandDTO(0, item_pos[0], item_pos[1]);
                    } else if (key == SDLK_y) {
                        waitForLeftClick(x, y);
                            command = new ThrowCommandDTO(
                                    gameRender->getInventoryItemByPosition(x, y));
                    } else if (key == SDLK_e) {
                        waitForLeftClick(x, y);
                        command = new EquipCommandDTO(
                                    gameRender->getInventoryItemByPosition(x, y));
                    } else if (key == SDLK_d) {
                        try {
                            waitForLeftClick(x, y);
                            std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
                            if (gameRender->isClickingInventoryItems(x, y))
                                command = new DepositItemCommandDTO(gameRender->getInventoryItemByPosition(x, y), npc_pos[0], npc_pos[1]);
                            else if (gameRender->isClickingInventoryGold(x, y))
                                command = new DepositGoldCommandDTO(1, npc_pos[0], npc_pos[1]);
                            else continue;
                        } catch (MapException& e) {
                            continue;
                        }
                    } else if (key == SDLK_w) {
                        try {
                            waitForLeftClick(x, y);
                            std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
                            if (gameRender->isClickingListItems(x, y))
                                command = new WithdrawItemCommandDTO(gameRender->getListItemByPosition(x, y), npc_pos[0], npc_pos[1]);
                            else if (gameRender->isClickingListGold(x, y))
                                command = new WithdrawGoldCommandDTO(1, npc_pos[0], npc_pos[1]);
                            else continue;
                        } catch (MapException& e) {
                            std::cout << e.what();
                            continue;
                        }
                    } else if (key == SDLK_s) {
                        try {
                            waitForLeftClick(x, y);
                            std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
                            if (gameRender->isClickingInventoryItems(x, y))
                                command = new SellItemCommandDTO(gameRender->getInventoryItemByPosition(x, y), npc_pos[0], npc_pos[1]);
                            else continue;
                        } catch (MapException& e) {
                            continue;
                        }
                    } else if (key == SDLK_b) {
                        try {
                            waitForLeftClick(x, y);
                            std::vector<int> npc_pos = mapMonitor.getNpcLookingAt();
                            if (gameRender->isClickingListItems(x, y))
                                command = new BuyItemCommandDTO(gameRender->getListItemByPosition(x, y), npc_pos[0], npc_pos[1]);
                            else continue;
                        } catch (MapException& e) {
                            continue;
                        }
                    } else {
                        continue;
                    }
                    std::cout << "\n\n\n estoy pusheando comando "<< (int) command->serialize()[0];

                    commandQueue.push(command);
                }
                catch (ItemException& e) {
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
    std::cout << "\n\n\nSALI DEL RUNNING!!!!\n\n\n";
}

void GameInputHandler::waitForLeftClick(int& x, int& y) {
    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        std::cout << "HICIERON ALGO Y ME FIJO SI ES CLICK IZQ\n";

        if (isLeftClick(event)) {
            std::cout << "\n\n sisi ES CLICK IZQ\n";
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
