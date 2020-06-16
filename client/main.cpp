#include <iostream>
#include <zconf.h>
#include "communication/client.h"
#include "communication/game_render.h"
#include "../common/socket_error.h"
#include "../server/defines.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 4

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./client hostname port username\n";
        return ERROR;
    }
    // TODO: esto se lee de una pantalla de login
    const char *host = argv[1], *port = argv[2], *username = argv[3];

    try {
        Client client(host, port, username);
        client.connectToServer();
        // TODO: este loop en realidad no va, pero si lo saco se cuelga
        std::string command;
        client.disconnectFromServer();
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return OK;
}
