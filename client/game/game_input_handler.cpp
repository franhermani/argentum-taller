#include <iostream>
#include "game_input_handler.h"
#include "map_monitor.h"
#include "../data_transfer_objects/move_command_dto.h"
#include "../data_transfer_objects/heal_command_dto.h"
#include "../data_transfer_objects/take_command_dto.h"
#include "../data_transfer_objects/throw_command_dto.h"
#include "../data_transfer_objects/revive_command_dto.h"
#include "../data_transfer_objects/meditate_command_dto.h"
#include "../data_transfer_objects/attack_command_dto.h"

GameInputHandler::GameInputHandler(BlockingQueue<CommandDTO*>& commandQueue, MapMonitor& mapMonitor):
commandQueue(commandQueue), mapMonitor(mapMonitor) {}

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
                } else if (keyEvent.keysym.sym == SDLK_a){
                    //attack
                    continue;
                } else if (keyEvent.keysym.sym == SDLK_h) {
                    //heal
                    continue;
                }
                else if (keyEvent.keysym.sym == SDLK_m){
                    command = new MeditateCommandDTO();
                }
                else if (keyEvent.keysym.sym == SDLK_r){
                    std::vector<int> priest_position = mapMonitor.getPriestLookingAt();
                    if(priest_position[0] == -1) command = new ReviveCommandDTO();
                    else command = new ReviveCommandDTO(priest_position[0], priest_position[1]);
                } else if (keyEvent.keysym.sym == SDLK_t) {
                    //take
                    continue;
                }
                else if (keyEvent.keysym.sym == SDLK_d) {
                    //trow (drop)
                    continue;
                }

                else {
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
