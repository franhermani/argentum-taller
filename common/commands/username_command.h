#ifndef USERNAME_COMMAND_H
#define USERNAME_COMMAND_H

#include <string>
#include <vector>
#include "command.h"

class UsernameCommand : public Command {
    std::string username;

public:
    // Constructor
    explicit UsernameCommand(const std::string& username);

    // Constructor y asignacion por copia deshabilitados
    UsernameCommand(const UsernameCommand&) = delete;
    UsernameCommand& operator=(const UsernameCommand&) = delete;

    // Destructor
    ~UsernameCommand() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;

    // Devuelve el username
    const std::string getUsername() const;
};

#endif // USERNAME_COMMAND_H
