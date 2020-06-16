
#include "game_input_handler.h"
#include <iostream>
#include <string>


void GameInputHandler::play() {
    try {
        bool running = true;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            Command* command;
            switch (event.type) {
                case SDL_KEYDOWN: {
                    auto& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            std::cout << "IZQ!!!\n";
                            command = new MoveCommand(LEFT);
                        case SDLK_RIGHT:
                            std::cout << "der!!!\n";
                            command = new MoveCommand(RIGHT);
                        case SDLK_UP:
                            std::cout << "arr!!!\n";
                            command = new MoveCommand(UP);
                        case SDLK_DOWN:
                            std::cout << "abaj!!!!!!\n";
                            command = new MoveCommand(DOWN);
                    }
                    commandQueue.push(command);
                }
                case SDL_QUIT:
                    std::cout << "Quit :(" << std::endl;
                    running = false;
                    break;
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

GameInputHandler::GameInputHandler(BlockingQueue<Command*>& commandQueue): commandQueue(commandQueue){}
GameInputHandler::~GameInputHandler() {}