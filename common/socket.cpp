#include <string.h>
#include <unistd.h>
#include <utility>
#include "socket.h"
#include "socket_error.h"
#include "socket_accept_error.h"

#define OK 0
#define ERROR 1
#define MAX_LISTEN_QUEUE_LEN 50

Socket::Socket(const char* host, const char* port, const bool is_server) :
sd(-1), isServer(is_server) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = isServer ? AI_PASSIVE : 0;
    _resolve_addr(host, port, hints);
}

Socket::Socket(const int sd) : sd(sd) {}

Socket::Socket(Socket &&other) : sd(other.sd) {
    other.sd = -1;
}

Socket& Socket::operator=(Socket &&other) {
    finish();
    sd = std::move(other.sd);
    return *this;
}

Socket::~Socket() {
    finish();
}

void Socket::finish() {
    if (sd == -1) return;
    shutdownChannel(SHUT_RDWR);
    closeSocketDescriptor();
}

void Socket::shutdownChannel(const int channel) {
    shutdown(sd, channel);
}

void Socket::closeSocketDescriptor() {
    if (sd == -1) return;
    close(sd);
    sd = -1;
}

void Socket::_resolve_addr(const char *host, const char *port,
        struct addrinfo& hints) {
    struct addrinfo *ai_list, *ptr;
    int sd_tmp, status;

    if ((status = getaddrinfo(host, port, &hints, &ai_list)) != 0)
        throw SocketError("Error in getaddrinfo: %s\n", gai_strerror(status));

    for (ptr = ai_list; ptr != NULL; ptr = ptr->ai_next) {
        sd_tmp = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sd_tmp == -1) continue;
        sd = sd_tmp;

        if (isServer) {
            if (_bind(ptr->ai_addr, ptr->ai_addrlen) == OK) break;
        } else {
            if (_connect(ptr->ai_addr, ptr->ai_addrlen) == OK) break;
        }
    }
    freeaddrinfo(ai_list);
    if (sd == -1) throw SocketError("No connections available\n");
}

const int Socket::_bind(struct sockaddr *addr, const socklen_t len) {
    int val = 1;

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1) {
        closeSocketDescriptor();
        return ERROR;
    }
    if (bind(sd, addr, len) == -1) {
        closeSocketDescriptor();
        return ERROR;
    }
    return OK;
}

const int Socket::_connect(struct sockaddr *addr, const socklen_t len) {
    if (connect(sd, addr, len) == -1) {
        closeSocketDescriptor();
        return ERROR;
    }
    return OK;
}

void Socket::listenToClients() {
    if (listen(sd, MAX_LISTEN_QUEUE_LEN) == -1) {
        closeSocketDescriptor();
        throw SocketError("Error listening to clients\n");
    }
}

Socket Socket::acceptClients() {
    int new_sd = accept(sd, NULL, NULL);
    if (new_sd == -1) throw SocketAcceptError();
    Socket accepted_socket(new_sd);
    return std::move(accepted_socket);
}

const int Socket::sendBytes(const char *buffer, const size_t length) {
    int bytes = 0;
    size_t tot_bytes = 0;
    bool socket_closed = false, socket_error = false;

    while (tot_bytes < length && (! socket_closed) && (! socket_error)) {
        bytes = send(sd, &buffer[tot_bytes], length - tot_bytes, MSG_NOSIGNAL);
        if (bytes == -1) {
            socket_error = true;
        } else if (bytes == 0) {
            socket_closed = true;
        } else {
            tot_bytes += bytes;
        }
    }
    if (socket_closed || socket_error)
        throw SocketError("Error sending bytes\n");

    return tot_bytes;
}

const int Socket::receiveBytes(char *buffer, const size_t length) {
    int bytes = 0;
    size_t tot_bytes = 0;
    bool socket_closed = false, socket_error = false;

    while ((tot_bytes < length) && (!socket_closed) && (! socket_error)) {
        bytes = recv(sd, &buffer[tot_bytes], length - tot_bytes, 0);
        if (bytes == -1) {
            socket_error = true;
        } else if (bytes == 0) {
            socket_closed = true;
        } else {
            tot_bytes += bytes;
        }
    }
    if (socket_closed || socket_error)
        throw SocketError("Error receiving bytes\n");

    return tot_bytes;
}
