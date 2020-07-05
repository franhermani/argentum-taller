
#include "exception.h"


MapException::MapException(const char *message) : message(message) {}

const char* MapException::what() const noexcept {
    return message.c_str();
}

InventoryException::InventoryException(const char *message) : message(message) {}

const char* InventoryException::what() const noexcept {
    return message.c_str();
}
