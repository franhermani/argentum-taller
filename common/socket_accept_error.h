#include <exception>

#ifndef SOCKET_ACCEPT_ERROR_H
#define SOCKET_ACCEPT_ERROR_H

struct SocketAcceptError : public std::exception {
    const char * what() const throw() {
        return "Error al aceptar al cliente\n";
    }
};

#endif // SOCKET_ACCEPT_ERROR_H
