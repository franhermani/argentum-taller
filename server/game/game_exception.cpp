#include "game_exception.h"

GameException::GameException(const int error_code) noexcept :
errorCode(error_code) {}

const int GameException::getErrorCode() const noexcept {
    return errorCode;
}
