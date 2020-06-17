#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>
#include "client.h"
#include "../sdl/window.h"
#include "../sdl/texture.h"
#include "vector"
#include "map"

void render_test_window();

Client::Client(const char *host, const char *port, const char *username) {
    gameHandler = new GameHandler(host, port, username);
}

Client::~Client() {
    delete gameHandler;
}

void Client::connectToServer() {
    gameHandler->run();
    //render_test_window();
}

void Client::disconnectFromServer() {
    gameHandler->stop();
}

// TODO: esto es de prueba
void Client::play() {
    try {
        SDLWindow window(800, 600);
        window.fill();
        // Usar factory
        SDLTexture im("../resources/images/guerrero.jpg", window);
        Area srcArea(0, 0, 300, 300);
        bool running = true;
        int x = 100;
        int y = 150;
        while (running) {
            SDL_Event event;
            Area destArea(x, y, 300, 300);
            window.fill();
            im.render(srcArea, destArea);
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
            window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}


void render_test_window() {
    int blocks_width = 20;
    int blocks_height = 30;
    GameRender GameRender(640*2, 480*2, blocks_width,blocks_height);

    //VECTOR DE TERRENOS QUE RECIBIRIAMOS POR SOCKET
    std::vector<Terrain> received_terrain;
    for (int i=0; i<blocks_width*blocks_height; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;

    //VECTOR DE CHARACTERS QUE RECIBIRIAMOS POR SOCKET
    std::vector<npc_pos> npc_positions;
    npc_pos npc_1 = {0, 0, WARRIOR_RIGHT};
    npc_pos npc_2 = {0, 10, SKELETON_DOWN};
    npc_positions.push_back(npc_1);
    npc_positions.push_back(npc_2);


    GameRender.render(received_terrain, npc_positions);

    //SIMULO QUE ME VAN LLEGANDO POR SOCKET+
    for (int i=0; i<10; i++) {
        for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
            it->x = it->x+1;
        }
        GameRender.render(received_terrain, npc_positions);
        usleep(500000);
    }

    //espero el quit
    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
    }
}
