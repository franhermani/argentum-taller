#ifndef ID_MANAGER_H
#define ID_MANAGER_H

#include <string>
#include <map>

class IdManager {
    int actual_player_id;
    int actual_creature_id;
    std::map<std::string, int> username_ids;

public:
    // Constructor
    IdManager();

    // Agrega un Player por username y devuelve su ID
    const int addPlayerByUsername(const std::string& username);

    // Agrega una criatura por ID y lo devuelve
    const int addCreatureById();

    // Elimina 'username' del map
    void removeUsername(const std::string& username);
};

#endif // ID_MANAGER_H
