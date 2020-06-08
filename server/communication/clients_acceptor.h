#ifndef CLIENTS_ACCEPTOR_H
#define CLIENTS_ACCEPTOR_H

#include <vector>
#include <atomic>
#include "../../common/thread.h"
#include "../../common/socket.h"
#include "client_handler.h"

class ClientsAcceptor : public Thread {
    Socket socket;
    std::vector<ClientHandler*> clients;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;

    // Crea el thread del cliente
    void createClientHandler();

    // Inicializa el thread del cliente
    void startClientHandler();

    // Recorre el vector de clientes y elimina aquellos que ya finalizaron
    // Libera la memoria reservada
    void cleanDeadClientHandlers();

    // Recorre el vector de clientes y espera a que finalicen
    // Libera la memoria reservada
    void joinClientHandlers();

public:
    // Constructor
    ClientsAcceptor(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    ClientsAcceptor(const ClientsAcceptor&) = delete;
    ClientsAcceptor& operator=(const ClientsAcceptor&) = delete;

    // Acepta clientes, crea sus threads, los almacena en el vector 'clients'
    // y los pone a correr
    void run() override;

    // Setea la variable booleana 'keep_talking' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o false en caso contrario
    bool isDead() override;
};

#endif // CLIENTS_ACCEPTOR_H
