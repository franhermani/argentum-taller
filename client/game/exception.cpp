
#include "exception.h"


MapException::MapException(const char *message) : message(message) {}

const char* MapException::what() const noexcept {
    return message.c_str();
}

ItemException::ItemException(const char *message) : message(message) {}

const char* ItemException::what() const noexcept {
    return message.c_str();
}

CommandCreationException::CommandCreationException(const char *message) : message(message) {}

const char* CommandCreationException::what() const noexcept {
    return message.c_str();
}
