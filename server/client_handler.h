#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>
#include "../common/thread.h"
#include "../common/socket.h"
#include "game/game_manager.h"
#include "communication/client_sender.h"
#include "communication/client_receiver.h"

class BlockingVector;

class ClientHandler : public Thread {
    Socket socket;
    GameManager& gameManager;
    BlockingVector& clients;
    ClientReceiver* clientReceiver;
    ClientSender* clientSender{};
    Player* player{};

    // Hace el chequeo del username en el mismo constructor
    // Si hay un error, le envia un mensaje al cliente y relanza la excepcion
    // para que luego la catchee el ClientsAcceptor
    // Si esta ok, crea al player y sigue con la ejecucion normal
    void checkUsername();

public:
    // Constructor
    ClientHandler(Socket socket, GameManager& game_manager,
            BlockingVector& clients);

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
