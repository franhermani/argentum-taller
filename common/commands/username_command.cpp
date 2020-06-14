#include <iostream>
#include <cstring>
#include <vector>
#include "username_command.h"
#include "defines.h"

UsernameCommand::UsernameCommand(const std::string& username) :
username(username) {}

UsernameCommand::~UsernameCommand() {}

const std::vector<char> UsernameCommand::serialize() const {
    // Longitud de los argumentos
    uint8_t arguments_size = username.length();

    // Longitud total
    size_t total_size = sizeof(uint8_t) + sizeof(uint8_t) + arguments_size;

    std::cout << username << "\n";

    // Vector serializado
    std::vector<char> byte_msg;
    byte_msg.resize(total_size);

    // Tipo de comando
    byte_msg[0] = CMD_USERNAME;

    // Longitud de los argumentos
    byte_msg[1] = arguments_size;

    // Argumentos
    memcpy(&byte_msg[2], username.c_str(), arguments_size);

    return byte_msg;
}

const std::string UsernameCommand::getUsername() const {
    return username;
}
