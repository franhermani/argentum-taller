#include <iostream>
#include <zconf.h>
#include "client.h"
#include "../common/socket_error.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 4

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./client <hostname> <port> <username>\n";
        return ERROR;
    }
    const char *host = argv[1], *port = argv[2], *username = argv[3];

    try {
        Client client(host, port, username);
        client.connectToServer();
        client.disconnectFromServer();
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return OK;
}
