#include <cstring>
#include <cerrno>
#include <cstdio>
#include <cstdarg>
#include "socket_error.h"

SocketError::SocketError(const char *fmt, ...) noexcept {
    memset(msgError, '\0', BUF_LEN);
    int errno_aux = errno;
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(msgError, BUF_LEN, fmt, args);
    va_end(args);
    strncpy(msgError + s, strerror(errno_aux), BUF_LEN - s);
    msgError[s] = '\0';
}

const char* SocketError::what() const noexcept {
    return msgError;
}
