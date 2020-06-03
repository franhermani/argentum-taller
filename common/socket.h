#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class Socket {
    int sd;
    bool isServer;

    // Obtiene addresses segun el 'host', 'port' y 'hints'
    // y selecciona la primera disponible
    // Lanza SocketError en caso de error
    void _resolve_addr(const char *host, const char *port,
            struct addrinfo& hints);

    // [Solo servidor]
    // Asocia un socket a un proceso dado
    // Devuelve OK o lanza SocketError en caso de error
    const int _bind(struct sockaddr *addr, const socklen_t len);

    // [Solo cliente]
    // Intenta conectarse a un socket servidor
    // Devuelve OK o lanza SocketError en caso de error
    const int _connect(struct sockaddr *addr, const socklen_t len);

    // Cierra el canal 'channel', el cual puede ser:
    // - SHUT_RD    --> Lectura
    // - SHUT_WR    --> Escritura
    // - SHUT_RDWR  --> Lectura y Escritura
    // Lanza SocketError en caso de error
    void shutdownChannel(const int channel);

    // Cierra el socket descriptor y le asigna un valor de -1
    void closeSocketDescriptor();

public:
    // Constructor
    // Crea un socket asociado al 'host' y 'port' y bindea (si es server)
    // o conecta (si es cliente) a la primera address disponible
    Socket(const char *host, const char *port, const bool is_server);

    // [Solo servidor]
    // Constructor para sockets devueltos por accept
    explicit Socket(const int sd);

    // Constructor y asignacion por copia deshabilitados
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // Constructor y asignacion por movimiento
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    // Destructor
    // Llama a finish
    ~Socket();

    // Cierra el canal de lectura-escritura y el socket descriptor
    // (en caso de que no se hayan cerrado antes)
    void finish();

    // [Solo servidor]
    // Escucha conexiones entrantes de clientes (hasta MAX_LISTEN_QUEUE_LEN)
    // Lanza SocketError en caso de error
    void listenToClients();

    // [Solo servidor]
    // Acepta conexiones entrantes de clientes (metodo bloqueante)
    // Devuelve un nuevo Socket asociado al cliente
    // Lanza SocketError en caso de error
    Socket acceptClients();

    // Intenta enviar 'length' bytes almacenados en 'buffer' a otro socket
    // Devuelve la cantidad de bytes enviados
    // Lanza SocketError en caso de error
    const int sendBytes(const char *buffer, const size_t length);

    // Intenta recibir 'length' bytes de otro socket y almacenarlos en 'buffer'
    // Devuelve la cantidad de bytes recibidos
    // Lanza SocketError en caso de error
    const int receiveBytes(char *buffer, const size_t length);
};

#endif // SOCKET_H
