#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

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

    // Envia el username a traves del socket
    void sendUsername(const std::string& username);

    // Envia un comando a traves del socket
    void sendCommand(CommandDTO& command);

    //recibe desde el servidor un vector de Terrains
    matrix_t receiveMatrix();

    //recibe desde el servidor el mundo actual y se lo pasa a gamerender para mostrarlo
    world_t receiveWorld();

    };

#endif // CLIENT_PROTOCOL_H
