#include <cstring>
#include <cerrno>
#include <cstdio>
#include <cstdarg>
#include "game_exception.h"

GameException::GameException(const char *fmt, ...) noexcept {
    int errno_aux = errno;
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(message, BUF_LEN, fmt, args);
    va_end(args);
    strncpy(message + s, strerror(errno_aux), BUF_LEN - s);
    message[BUF_LEN - 1] = '\0';
}

const char* GameException::what() const noexcept {
    return message;
}
