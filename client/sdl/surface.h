#ifndef SURFACE_H
#define SURFACE_H

#include <string>

class SDLWindow;
class SDL_Surface;

class Surface {
    SDL_Surface* surface;

public:
    // Constructor
    Surface(const std::string filename, const SDLWindow& window);

    // Destructor
    ~Surface();

    // Devuelve SDL_Surface para poder ser estampado
    SDL_Surface* getRenderableSurface();
};

#endif // SURFACE_H
