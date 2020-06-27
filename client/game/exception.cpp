
#include "exception.h"


GameException::GameException(const char *message) : message(message) {}

const char* GameException::what() const noexcept {
    return message.c_str();
}
