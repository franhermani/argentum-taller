#ifndef ARGENTUM_EXCEPTION_H
#define ARGENTUM_EXCEPTION_H
#include <exception>
#include <typeinfo>
#include <string>


class MapException :  public std::exception{
    std::string message;
public:
    // Constructor
     explicit MapException(const char *message);

    // Devuelve el mensaje de error
    const char * what() const noexcept;
};

class InventoryException :  public std::exception{
    std::string message;
public:
    // Constructor
    explicit InventoryException(const char *message);

    // Devuelve el mensaje de error
    const char * what() const noexcept;
};


#endif //ARGENTUM_EXCEPTION_H
