#ifndef MESSAGES_H
#define MESSAGES_H

enum messageType {
    // Actualizaciones del mundo
    MSG_WORLD_UPDATE,

    // Respuesta al comando Listar
    MSG_CMD_LIST,

    // Excepciones del juego
    MSG_GAME_EXCEPTION
};

#endif // MESSAGES_H
