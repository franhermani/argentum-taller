#ifndef CLIENTS_CLEANER_H
#define CLIENTS_CLEANER_H

#include <vector>
#include "../../common/thread.h"
#include "clients_blocking_vector.h"

class ClientsCleaner : public Thread {
    ClientsBlockingVector& clients;

public:
    // Constructor
    explicit ClientsCleaner(ClientsBlockingVector& clients);

    // Constructor y asignacion por copia deshabilitados
    ClientsCleaner(const ClientsCleaner&) = delete;
    ClientsCleaner& operator=(const ClientsCleaner&) = delete;

    // Recorre el vector de clientes y elimina aquellos que ya finalizaron
    // Libera la memoria reservada
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o false en caso contrario
    bool isDead() override;
};


#endif // CLIENTS_CLEANER_H
