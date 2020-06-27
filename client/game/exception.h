#ifndef ARGENTUM_EXCEPTION_H
#define ARGENTUM_EXCEPTION_H
#include <exception>
#include <typeinfo>
#include <string>


class GameException :  public std::exception{
    std::string message;
public:
    // Constructor
    GameException(const char *message);

    // Devuelve el mensaje de error
    const char * what() const noexcept;
};


#endif //ARGENTUM_EXCEPTION_H
