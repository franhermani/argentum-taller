#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include <vector>
#include <atomic>
#include "../common/thread.h"
#include "../common/socket.h"
#include "thread_client.h"

class ThreadAcceptor : public Thread {
    Socket socket;
    std::vector<ThreadClient*> clients;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;

    // Crea el thread del cliente
    void createThreadClient();

    // Inicializa el thread del cliente
    void startThreadClient();

    // Recorre el vector de clientes y elimina aquellos que ya finalizaron
    // Libera la memoria reservada
    void cleanDeadClients();

    // Recorre el vector de clientes y espera a que finalicen
    // Libera la memoria reservada
    void joinClients();

public:
    // Constructor
    ThreadAcceptor(const char *host, const char *port);

    // Constructor y asignacion por copia deshabilitados
    ThreadAcceptor(const ThreadAcceptor&) = delete;
    ThreadAcceptor& operator=(const ThreadAcceptor&) = delete;

    // Acepta clientes, crea sus threads, los almacena en el vector 'clients'
    // y los pone a correr
    virtual void run() override;

    // Setea la variable booleana 'keep_talking' en false
    virtual void stop() override;

    // Devuelve true si el thread no esta corriendo o false en caso contrario
    virtual const bool isDead() override;
};

#endif // THREAD_ACCEPTOR_H
