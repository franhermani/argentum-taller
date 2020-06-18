#include "username_command.h"

UsernameCommand::UsernameCommand(const std::string& username) :
username(username) {}

UsernameCommand::~UsernameCommand() = default;

const std::string UsernameCommand::getUsername() const {
    return username;
}
