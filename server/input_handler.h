#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "commands/command.h"
#include "commands/move_command.h"


class InputHandler {
    Command* moveComand;

public:
    // Constructor
    InputHandler();

    // Constructor y asignacion por copia deshabilitados
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    // Crea un comando y lo devuelve segun el input recibido
    Command* handleInput();
};

#endif // INPUT_HANDLER_H
