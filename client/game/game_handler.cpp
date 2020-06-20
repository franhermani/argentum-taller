#include <iostream>
#include <vector>
#include <zconf.h>
#include "game_handler.h"

GameHandler::GameHandler(const char *host, const char *port,
        const char *username) : socket(host, port, false),
        gameRender(640*2, 480*2) {
    connectionSender = new ConnectionSender(socket, commandQueue);
    connectionSender->sendUsername(username);
    inputHandler = new GameInputHandler(commandQueue);
    //TODO borrar
    gameRender.setTilesSize(10,10);
    connectionReceiver = new ConnectionReceiver(socket, gameRender);
}

GameHandler::~GameHandler() {
    delete connectionSender;
    delete connectionReceiver;
    delete inputHandler;
}

void GameHandler::run() {
    //render_test_window();
    connectionSender->start();
    connectionReceiver->start();
    inputHandler->run();
}

void GameHandler::stop() {
    commandQueue.close();
    connectionSender->stop();
    connectionSender->join();
    connectionReceiver->stop();
    connectionReceiver->join();
}

void GameHandler::render_test_window() {
    //VECTOR DE TERRENOS QUE RECIBIRIAMOS POR SOCKET
    std::vector<Terrain> received_terrain;
    for (int i = 0; i < 20 * 30; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;

    //VECTOR DE CHARACTERS QUE RECIBIRIAMOS POR SOCKET
    std::vector<npc_pos> npc_positions;
    npc_pos npc_1 = {0, 0, WARRIOR_RIGHT};
    npc_pos npc_2 = {3, 10, SKELETON_RIGHT};
    npc_positions.push_back(npc_1);
    npc_positions.push_back(npc_2);

    gameRender.render(received_terrain, npc_positions);

    //SIMULO QUE ME VAN LLEGANDO POR SOCKET+
    for (int i = 0; i < 10; i++) {
        for (auto it = std::begin(npc_positions);
        it != std::end(npc_positions); ++it) {
            it->x = it->x + 1;
        }
        gameRender.render(received_terrain, npc_positions);
        usleep(100000);
    }
}
