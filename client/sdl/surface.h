//
// Created by martinrosas on 14/6/20.
//

#ifndef ARGENTUM_SURFACE_H
#define ARGENTUM_SURFACE_H

class SDL_Surface;
class Surface {
    SDL_Surface surface;

public:
    // Constructor
    SDLSurface(const std::string filename);

    // Destructor
    ~SDLSurface();

    SDL_Surface* get_renderable_surface();
};


#endif //ARGENTUM_SURFACE_H
