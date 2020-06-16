#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>
#include "../../common/thread.h"
#include "../../common/socket.h"
#include "client_sender.h"
#include "client_receiver.h"
#include "../game/game_manager.h"

class ClientHandler : public Thread {
    Socket socket;
    GameManager& gameManager;
    ClientReceiver* clientReceiver;
    ClientSender* clientSender;
    Player* player{};

public:
    // Constructor
    ClientHandler(Socket socket, GameManager& game_manager);

    // Constructor y asignacion por copia deshabilitados
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    // Destructor
    // Elimina la memoria reservada para los thread sender y receiver
    ~ClientHandler();

    // Inicializa los thread sender y receiver
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};

#endif // CLIENT_HANDLER_H
