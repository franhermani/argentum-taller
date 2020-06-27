#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>

class GameException : public std::exception {
    int errorCode;

public:
    // Constructor
    explicit GameException(const int error_code) noexcept;

    // Devuelve el codigo de error
    const int getErrorCode() const noexcept;
};

#endif // GAME_EXCEPTION_H
