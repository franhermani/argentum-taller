#include <iostream>
#include <exception>
#include "server.h"
#include "../common/utilities/file.h"

#define OK          0
#define ERROR       1
#define NUM_PARAMS  2
#define EXIT_CHAR   "q"

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./server <archivo_de_configuracion>\n";
        return ERROR;
    }
    std::string path = argv[1], command;

    try {
        File file(path);
        Server server(file);
        server.startGame();
        while (getline(std::cin, command))
            if (command == EXIT_CHAR) break;
        server.endGame();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return ERROR;
    } catch (...) {
        std::cerr << "Error desconocido\n";
        return ERROR;
    }
    return OK;
}
