#include <iostream>
#include "game_input_handler.h"
#include "map_monitor.h"
#include "exception.h"
#include "../data_transfer_objects/command_dto_manager.h"
#include <vector>

GameInputHandler::GameInputHandler(BlockingQueue<CommandDTO*>& commandQueue,
            MapMonitor& mapMonitor, GameRender* gameRender):
commandQueue(commandQueue), mapMonitor(mapMonitor), gameRender(gameRender) {}

GameInputHandler::~GameInputHandler() = default;

void GameInputHandler::play() {
    try {
        bool running = true;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            CommandDTO* command;
            CommandDTOManager command_manager(mapMonitor, gameRender);
            if (event.type == SDL_KEYDOWN) {
                auto &keyEvent = (SDL_KeyboardEvent &) event;
                int key = keyEvent.keysym.sym;
                try {
                    command = command_manager(key);
                    commandQueue.push(command);
                }
                catch (ItemException& e) {
                    continue;
                } catch (MapException& e) {
                    continue;
                } catch(CommandCreationException& e) {
                    continue;
                }
                catch (StopGameException& e){
                    running = false;
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


void GameInputHandler::run() {
    play();
}

