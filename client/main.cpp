#include <iostream>
#include "communication/client.h"
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
//        client.disconnectFromServer();
//        client.play();
        // TODO: este loop en realidad no va, pero si lo saco se cuelga
        std::string command;
        while (getline(std::cin, command))
            if (command == EXIT_CHAR) break;
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return OK;
}
