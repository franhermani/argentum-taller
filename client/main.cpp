#include <iostream>
#include <zconf.h>
#include "communication/client.h"
#include "communication/game_render.h"
#include "../common/socket_error.h"
#include "../server/defines.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 1

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./client\n";
        return ERROR;
    }
    // TODO: esto se lee de una pantalla de login
    const char *host = "localhost", *port = "8080";

    try {
        Client client(host, port);
        client.connectToServer();

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


        GameRender.play(received_terrain, npc_positions);

        //SIMULO QUE ME VAN LLEGANDO POR SOCKET+
        for (int i=0; i<10; i++) {
            for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
                it->x = it->x+1;
            }
            GameRender.play(received_terrain, npc_positions);
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

//        client.disconnectFromServer();
//        client.play();
//        client.render_map();
        // TODO: este loop en realidad no va, pero si lo saco se cuelga
        std::string command;
        while (getline(std::cin, command))
            if (command == EXIT_CHAR) break;
        client.disconnectFromServer();
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return OK;
}
