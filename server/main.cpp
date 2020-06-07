#include <iostream>
#include <exception>
#include "defines.h"
#include "utilities/file.h"
#include "communication/server.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 2

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./server <archivo_de_configuracion>\n";
        return ERROR;
    }
    std::string path = argv[1];

    try {
        File file(path);
        Server server(file);
        server.startThreadAcceptor();
        std::string command;
        while (getline(std::cin, command))
            if (command == EXIT_CHAR) break;

        server.stopThreadAcceptor();
        server.joinThreadAcceptor();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return ERROR;
    } catch (...) {
        std::cerr << "Error desconocido\n";
        return ERROR;
    }
    return OK;
}
