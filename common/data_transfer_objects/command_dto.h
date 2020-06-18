#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include <vector>
#include <string>

class CommandDTO {
public:
    // Destructor
    virtual ~CommandDTO();

    // Devuelve la serializacion en bytes del comando
    // Metodo a definir por las clases derivadas
    virtual const std::vector<char> serialize() const = 0;
};

#endif // COMMAND_DTO_H
