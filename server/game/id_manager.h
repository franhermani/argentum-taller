#ifndef ID_MANAGER_H
#define ID_MANAGER_H

#include <string>
#include <map>

struct NoMoreAvailableIdsException : public std::exception {
    const char* what() const throw() {
        return "No more available Ids in the game\n";
    }
};

class IdManager {
    int actual_player_id;
    int actual_npc_id;
    int actual_item_id;
    std::map<std::string, int> username_ids;

public:
    // Constructor
    IdManager();

    // Obtiene el ID de un Player por username
    // Si no existe lo agrega al map
    const int getPlayerByUsername(const std::string& username);

    // Agrega un NPC por ID
    void addNPCById();

    // Agrega un Item por ID
    void addItemById();
};

#endif // ID_MANAGER_H
