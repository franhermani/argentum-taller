//
// Created by martinrosas on 14/6/20.
//

#include "surface.h"
#include <SDL2/SDL.h>


Surface::Surface(const std::string filename, const SDLWindow &window) {
    surface = loadSurface(filename);
    if (! surface)
        throw SDLException("Error al cargar la surface", SDL_GetError());
}

Surface::~Surface() {
    SDL_FreeSurface(surface);
}

SDL_Surface* Surface::get_renderable_surface() {
    return surface;
}
