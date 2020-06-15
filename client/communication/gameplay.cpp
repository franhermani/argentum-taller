
#include "gameplay.h"
#include <iostream>
#include <string>


void Gameplay::play() {
    try {
        bool running = true;
        int x = 100;
        int y = 150;
        while (running) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN: {
                    auto& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            x -= 10;
                            break;
                        case SDLK_RIGHT:
                            x += 10;
                            break;
                        case SDLK_UP:
                            y -= 10;
                            break;
                        case SDLK_DOWN:
                            y += 10;
                            break;
                    }
                } // Fin KEY_DOWN
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "Oh! Mouse" << std::endl;
                    break;
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


Gameplay::Gameplay() {}

Gameplay::~Gameplay() {}


void Gameplay::run() {
    play();
}

void Gameplay::stop() {
    keepRunning = false;
}

bool Gameplay::isDead() {
    return (! isRunning);

}