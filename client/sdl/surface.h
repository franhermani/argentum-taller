#ifndef SURFACE_H
#define SURFACE_H
#include <SDL2/SDL_ttf.h>
#include <string>

class SDLWindow;
class SDL_Surface;

class Surface {
    SDL_Surface* surface;

public:
    // ConstructorSurface
    Surface(const std::string filename, const SDLWindow& window,
            int isTransparent);
    // Constructor surface de texto
    Surface(const std::string text, const SDLWindow &window,
            TTF_Font* font, SDL_Color& color);

    // Destructor
    ~Surface();

    // Constructor y asignacion por copia deshabilitados
    Surface(const Surface &) = delete;

    Surface &operator=(const Surface &) = delete;


    // Devuelve SDL_Surface para poder ser estampado
    SDL_Surface* getRenderable();
};

#endif // SURFACE_H
