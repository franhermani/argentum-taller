#include <iostream>
#include <string>
#include "game_input_handler.h"

GameInputHandler::GameInputHandler(BlockingQueue<Command*>& commandQueue):
commandQueue(commandQueue) {}

GameInputHandler::~GameInputHandler() = default;

void GameInputHandler::play() {
    try {
        bool running = true;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            Command *command;
            if (event.type == SDL_KEYDOWN) {
                auto &keyEvent = (SDL_KeyboardEvent &) event;
                if (keyEvent.keysym.sym == SDLK_LEFT)
                    command = new MoveCommand(LEFT);
                else if (keyEvent.keysym.sym == SDLK_RIGHT)
                    command = new MoveCommand(RIGHT);
                else if (keyEvent.keysym.sym == SDLK_UP)
                    command = new MoveCommand(UP);
                else if (keyEvent.keysym.sym == SDLK_DOWN)
                    command = new MoveCommand(DOWN);
                else if (keyEvent.keysym.sym == SDLK_ESCAPE) {
                    //aca en realidad se va a mandar el comando de salir
                    running = false;
                    continue;
                }
                else continue;
                commandQueue.push(command);
            } else if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_KEYUP)
                continue;
            else {
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
