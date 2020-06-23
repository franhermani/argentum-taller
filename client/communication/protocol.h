#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <vector>
#include <string>
#include "../../common/socket.h"
#include "../data_transfer_objects/command_dto.h"
#include "../../common/defines/terrains.h"
#include "../game/game_render.h"

class ClientProtocol {
    Socket& socket;

public:
    // Constructor
    explicit ClientProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    // Envia la informacion del player a traves del socket
    void sendPlayerInfo(const std::string& username, const uint8_t race_type,
            const uint8_t class_type);

    // Recibe el codigo de confirmacion del server por el username enviado
    const int receiveUsernameConfirmation();

    // Recibe el id del username
    const int receiveUsernameId();

    // Recibe la vision del player medida en bloques (alto y ancho)
    const std::vector<int> receiveBlocksAround();

    // Envia un comando a traves del socket
    void sendCommand(CommandDTO& command);

    //recibe desde el servidor un vector de Terrains
    matrix_t receiveMatrix();

    //recibe desde el servidor el mundo actual
    world_t receiveWorld();
    };

#endif // CLIENT_PROTOCOL_H
