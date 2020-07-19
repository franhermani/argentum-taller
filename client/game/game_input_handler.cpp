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
            CommandDTOManager command_manager(mapMonitor, gameRender, *this);
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


int GameInputHandler::isLeftClick(SDL_Event& event) {
    return ((event.type == SDL_MOUSEBUTTONDOWN) &&
            (event.button.button == SDL_BUTTON_LEFT));
}

int GameInputHandler::isMoveKey(SDL_Event& event) {
    auto &keyEvent = (SDL_KeyboardEvent &) event;
    int key = keyEvent.keysym.sym;
    if ((event.type == SDL_KEYDOWN) & ((key == SDLK_DOWN)
                                       || (key == SDLK_UP) || (key == SDLK_LEFT) || (key == SDLK_RIGHT)))
        return true;
    return false;
}

void GameInputHandler::waitForLeftClick(int& x, int& y) {
    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        if (isLeftClick(event)) {
            SDL_GetMouseState(&x, &y);
            return;
        }
        if (isMoveKey(event)) {
            throw CommandCreationException("Cancelado por "
                                           "tecla de movimiento");
        }

    }
}


void GameInputHandler::run() {
    play();
}

