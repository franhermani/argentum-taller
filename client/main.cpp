#include <iostream>
#include <string>
#include <set>
#include <zconf.h>
#include "client.h"
#include "../common/socket_error.h"
#include "../common/defines/username_codes.h"
#include "sdl/exception.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 3

const std::string readUsername();
const uint8_t readRaceType();
const uint8_t readClassType();

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./client <hostname> <port>\n";
        return ERROR;
    }
    const char *host = argv[1], *port = argv[2];
    std::string username = readUsername();
    uint8_t race_type = readRaceType(),
            class_type = readClassType();

    try {
        Client client(host, port, username, race_type, class_type);
        client.connectToServer();
        client.disconnectFromServer();
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(DuplicatedUsernameException& e) {
        std::cerr << e.what() << "\n";
    } catch(NoMoreAvailableIdsException& e) {
        std::cerr << e.what() << "\n";
    } catch(SDLException& e) {
        std::cerr << e.what() << "\n";
    } catch(SoundException& e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return OK;
}

const std::string readUsername() {
    std::string username;

    std::cout << "\n¡Bienvenido al Argentum 2020!\n\n";
    std::cout << "Indique su nombre de usuario: ";
    std::cin >> username;
    std::cout << "\nHola, " << username << ".";
    std::cout << "\n¡Es hora de crear tu personaje!\n\n";

    return username;
}

const uint8_t readRaceType() {
    std::string race_type;
    std::set<std::string> valid_numbers = {"1", "2", "3", "4"};

    std::cout << "Primero, elige una de las siguientes razas "
                 "para tu personaje:\n";
    std::cout <<
              "1. Humano\n" <<
              "2. Elfo\n" <<
              "3. Enano\n" <<
              "4. Gnomo\n";

    std::cout << "\nElige una raza ingresando el número correspondiente: ";
    std::cin >> race_type;
    while (valid_numbers.count(race_type) == 0) {
        std::cout << "Por favor, ingrese un número válido: ";
        std::cin >> race_type;
    }
    return std::stoi(race_type);
}

const uint8_t readClassType() {
    std::string class_type;
    std::set<std::string> valid_numbers = {"1", "2", "3", "4"};

    std::cout << "\n¡Muy bien! Ahora, elige una de las siguientes clases "
                 "para tu personaje:\n";

    std::cout <<
              "1. Mago\n" <<
              "2. Clérigo\n" <<
              "3. Paladin\n" <<
              "4. Guerrero\n";
    std::cout << "\nElige una clase ingresando el número correspondiente: ";
    std::cin >> class_type;
    while (valid_numbers.count(class_type) == 0) {
        std::cout << "Por favor, ingrese un número válido: ";
        std::cin >> class_type;
    }
    return std::stoi(class_type);
}
