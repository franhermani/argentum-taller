#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <vector>
#include "../../common/socket.h"
#include "../game/commands/command_factory.h"
#include "../game/commands/command.h"
#include "../game/world_monitor.h"

class ServerProtocol {
    Socket& socket;
    CommandFactory commandFactory;

    void loadPlayerInfo(world_t& w, Player& player);
    void loadPlayers(world_t& w, std::vector<Player*>& players);
    void loadCreatures(world_t& w, std::vector<Creature*>& creatures);
    void loadItems(world_t& w, std::vector<Item*>& items);
    void loadGolds(world_t& w, std::vector<Gold*>& golds);
    void loadAttacks(world_t& w, std::vector<Attack*>& attacks);

    void writePlayerInfo(std::vector<char>& byte_msg, int& pos, world_t& w);
    void writePlayers(std::vector<char>& byte_msg, int& pos, world_t& w);
    void writeCreatures(std::vector<char>& byte_msg, int& pos, world_t& w);
    void writeItems(std::vector<char>& byte_msg, int& pos, world_t& w);
    void writeGolds(std::vector<char>& byte_msg, int& pos, world_t& w);
    void writeAttacks(std::vector<char>& byte_msg, int& pos, world_t& w);

public:
    // Constructor
    explicit ServerProtocol(Socket& socket);

    // Constructor y asignacion por copia deshabilitados
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Recibe la info del player del cliente a traves del socket
    const std::vector<char> receivePlayerInfo();

    // Recibe un commandDTO del cliente a traves del socket
    // Llama al CommandFactory y devuelve una clase derivada de command
    Command* receiveCommand(Player& player);

    // Envia un codigo de confirmacion del username al cliente
    void sendUsernameConfirmation(int code);

    // Envia el id del username para que el cliente lo almacene
    void sendUsernameId(Player& player);

    // Envia la vision del player en bloques (alto y ancho)
    void sendBlocksAround(int width, int height);

    // Envia las dimensiones del mapa en bloques (alto y ancho)
    void sendMapDimensions(WorldMonitor& world_monitor);

    // Envia la lista de NPCs a traves del socket
    void sendNPCs(WorldMonitor& world_monitor);

    // Envia una actualizacion del mundo a traves del socket
    void sendWorldUpdate(WorldMonitor& world_monitor, Player& player);

    // Envia un listado de items a traves del socket (incluye oro)
    void sendItemsList(list_t& list);

    // Envia un mensaje del juego a traves del socket
    void sendGameMessage(const std::string& message);
};

#endif // SERVER_PROTOCOL_H
