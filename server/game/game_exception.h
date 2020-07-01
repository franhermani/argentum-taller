#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>
#include <typeinfo>

#define BUF_LEN 256

class GameException : public std::exception {
    int playerId;
    char message[BUF_LEN]{};

public:
    // Constructor con parametros variables
    explicit GameException(const int player_id, const char *fmt, ...) noexcept;

    // Devuelve el id del player
    const int getPlayerId() const noexcept;

    // Devuelve el mensaje de excepcion
    virtual const char* what() const noexcept;
};

#endif // GAME_EXCEPTION_H
