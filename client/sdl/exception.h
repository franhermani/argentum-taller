#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H

#include <string>
#include <exception>

class SDLException : public std::exception {
    std::string message;
public:
    // Constructor
    SDLException(const char *message, const char *sdl_error);

    // Devuelve el mensaje de error
    const char * what() const noexcept;
};

class SurfaceExistanceException : public std::exception {
    std::string message;
public:
    // Constructor
    explicit SurfaceExistanceException(const char *message);

    // Devuelve el mensaje de error
    const char * what() const noexcept;
};


#endif // SDL_EXCEPTION_H
