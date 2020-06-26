#ifndef CLIENTS_ACCEPTOR_H
#define CLIENTS_ACCEPTOR_H

#include <vector>
#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../utilities/blocking_vector.h"
#include "clients_cleaner.h"
#include "../game/game_manager.h"

class ClientsAcceptor : public Thread {
    Socket socket;
    BlockingVector clients;
    ClientsCleaner* clientsCleaner;
    GameManager& gameManager;

public:
    // Constructor
    ClientsAcceptor(const char *host, const char *port,
            GameManager& game_manager);

    // Constructor y asignacion por copia deshabilitados
    ClientsAcceptor(const ClientsAcceptor&) = delete;
    ClientsAcceptor& operator=(const ClientsAcceptor&) = delete;

    // Destructor
    // Libera la memoria reservada para ClientsCleaner
    ~ClientsAcceptor();

    // Acepta clientes, crea sus threads, los almacena en el vector 'clients'
    // y los pone a correr
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o false en caso contrario
    bool isDead() override;
};

#endif // CLIENTS_ACCEPTOR_H
