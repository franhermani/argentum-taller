
#include "gameplay.h"
#include <iostream>
#include <string>


void Gameplay::play() {
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
                            command = new MoveCommand(LEFT);
                        case SDLK_RIGHT:
                            command = new MoveCommand(RIGHT);
                        case SDLK_UP:
                            command = new MoveCommand(UP);
                        case SDLK_DOWN:
                            command = new MoveCommand(DOWN);
                    }
                    commandQueue.push(command);
                } // Fin KEY_DOWN
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



void Gameplay::run() {
    play();
}

void Gameplay::stop() {
    keepRunning = false;
}

bool Gameplay::isDead() {
    return (! isRunning);
}

Gameplay::Gameplay(BlockingQueue<Command*>& commandQueue): commandQueue(commandQueue){}
Gameplay::~Gameplay() {}