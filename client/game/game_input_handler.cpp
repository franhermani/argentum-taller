#include <iostream>
#include "game_input_handler.h"
#include "../data_transfer_objects/move_command_dto.h"

GameInputHandler::GameInputHandler(ProtectedQueue<CommandDTO*>& commandQueue):
commandQueue(commandQueue) {}

GameInputHandler::~GameInputHandler() = default;

void GameInputHandler::play() {
    try {
        bool running = true;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            CommandDTO *command;
            if (event.type == SDL_KEYDOWN) {
                auto &keyEvent = (SDL_KeyboardEvent &) event;
                if (keyEvent.keysym.sym == SDLK_LEFT) {
                    command = new MoveCommandDTO(LEFT);
                } else if (keyEvent.keysym.sym == SDLK_RIGHT) {
                    command = new MoveCommandDTO(RIGHT);
                } else if (keyEvent.keysym.sym == SDLK_UP) {
                    command = new MoveCommandDTO(UP);
                } else if (keyEvent.keysym.sym == SDLK_DOWN) {
                    command = new MoveCommandDTO(DOWN);
                } else if (keyEvent.keysym.sym == SDLK_ESCAPE) {
                    // TODO: aca en realidad se va a mandar el comando de salir
                    running = false;
                    continue;
                } else {
                    continue;
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
