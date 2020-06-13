#ifndef ID_MANAGER_H
#define ID_MANAGER_H

#include <string>
#include <map>

struct NoMoreAvailableIdsException : public std::exception {
    const char* what() const throw() {
        return "No more available Ids in the game\n";
    }
};

struct DuplicatedUsernameException : public std::exception {
    const char* what() const throw() {
        return "This username already exists\n";
    }
};

struct UnexistentUsernameException : public std::exception {
    const char* what() const throw() {
        return "This username has not been registered\n";
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

    // Agrega un Player por username y devuelve su ID
    const int addPlayerByUsername(const std::string& username);

    // Agrega un NPC por ID y lo devuelve
    const int addNPCById();

    // Agrega un Item por ID y lo devuelve
    const int addItemById();

    // Obtiene el ID de un Player por username
    const int getPlayerId(const std::string& username);
};

#endif // ID_MANAGER_H
