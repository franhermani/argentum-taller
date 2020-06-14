
#include "surface.h"
#include "exception.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"


Surface::Surface(const std::string filename, const SDLWindow& window) {
    SDL_Surface* basic_surface = IMG_Load(filename.c_str());
    if (!basic_surface)
        throw SDLException("Error al cargar la surface", SDL_GetError());
    SDL_Surface* optimized_surface = SDL_ConvertSurface( basic_surface, window.getSurfaceFormat(), 0 );
    SDL_FreeSurface(basic_surface);
    if(!optimized_surface)
        throw SDLException("Error al optimizar la surface", SDL_GetError());
    surface = optimized_surface;
}

Surface::~Surface() {
    SDL_FreeSurface(surface);
}

SDL_Surface* Surface::get_renderable_surface() {
    return surface;
}
