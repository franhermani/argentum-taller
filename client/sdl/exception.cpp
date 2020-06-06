#include <string>
#include "exception.h"

SDLException::SDLException(const char *message, const char *sdl_error) :
std::exception(), message(message) {
    this->message.append("\nSDL_ERROR: ").append(sdl_error);
}

const char* SDLException::what() const noexcept {
    return message.c_str();
}
