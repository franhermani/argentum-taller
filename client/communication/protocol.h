#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <vector>
#include <string>
#include "../../common/socket.h"
#include "../data_transfer_objects/command_dto.h"
#include "../../common/defines/world_structs.h"

class ClientProtocol {
    Socket& socket;

    void loadPlayerInfo(std::vector<char>& buffer, int& pos, world_t& w);
    void loadPlayers(std::vector<char>& buffer, int& pos, world_t& w);
    void loadCreatures(std::vector<char>& buffer, int& pos, world_t& w);
    void loadItems(std::vector<char>& buffer, int& pos, world_t& w);
    void loadGolds(std::vector<char>& buffer, int& pos, world_t& w);
    void loadAttacks(std::vector<char>& buffer, int& pos, world_t& w);

public:
    // Constructor
    explicit ClientProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    // Envia un comando a traves del socket
    void sendCommand(CommandDTO& command);

    // Envia la informacion del player a traves del socket
    void sendPlayerInfo(const std::string& username, const uint8_t race_type,
            const uint8_t class_type);

    // Recibe el codigo de confirmacion del server por el username enviado
    const int receiveUsernameConfirmation();

    // Recibe el id del username
    const int receiveUsernameId();

    // Recibe la vision del player en bloques (alto y ancho)
    const std::vector<int> receiveBlocksAround();

    // Recibe las dimensiones del mapa en bloques (alto y ancho)
    const std::vector<int> receiveMapDimensions();

    // Recibe la lista de NPCs
    npcs_t receiveNPCs();

    // Recibe una actualizacion del mundo
    world_t receiveWorldUpdate();

    // Recibe un listado de items (incluye oro)
    // TODO: devolver vector de structs
    list_t receiveItemsList();

    // Recibe un mensaje del juego
    const std::string receiveGameMessage();
};

#endif // CLIENT_PROTOCOL_H
