#include <cstring>
#include <cerrno>
#include <cstdio>
#include <cstdarg>
#include "game_exception.h"

GameException::GameException(const int player_id, const char *fmt, ...)
noexcept : playerId(player_id) {
    memset(message, '\0', BUF_LEN);
    int errno_aux = errno;
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(message, BUF_LEN, fmt, args);
    va_end(args);
    strncpy(message + s, strerror(errno_aux), BUF_LEN - s);
    message[s] = '\0';
}

const int GameException::getPlayerId() const noexcept {
    return playerId;
}

const char* GameException::what() const noexcept {
    return message;
}
