#ifndef USERNAME_COMMAND_DTO_H
#define USERNAME_COMMAND_DTO_H

#include <string>
#include <vector>
#include "command_dto.h"

class UsernameCommandDTO : public CommandDTO {
    std::string username;

public:
    // Constructor
    explicit UsernameCommandDTO(const std::string& username);

    // Constructor y asignacion por copia deshabilitados
    UsernameCommandDTO(const UsernameCommandDTO&) = delete;
    UsernameCommandDTO& operator=(const UsernameCommandDTO&) = delete;

    // Destructor
    ~UsernameCommandDTO() override;

    // Devuelve la serializacion en bytes del comando
    const std::vector<char> serialize() const override;
};

#endif // USERNAME_COMMAND_H
