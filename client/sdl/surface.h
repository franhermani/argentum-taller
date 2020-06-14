
#ifndef ARGENTUM_SURFACE_H
#define ARGENTUM_SURFACE_H
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
    SDL_Surface* get_renderable_surface();
};


#endif //ARGENTUM_SURFACE_H
