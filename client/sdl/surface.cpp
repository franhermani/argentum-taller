#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "surface.h"
#include "exception.h"
#include "window.h"

Surface::Surface(const std::string filename, const SDLWindow& window, int isTransparent) {
    if (not isTransparent) {
        SDL_Surface* basic_surface = IMG_Load(filename.c_str());
        if (!basic_surface) {
            throw SDLException(filename.c_str(), SDL_GetError());
        }

        SDL_Surface *optimized_surface = SDL_ConvertSurface(
                basic_surface, window.getSurfaceFormat(), 0);

        SDL_FreeSurface(basic_surface);

        if (!optimized_surface)
            throw SDLException("Error al optimizar la surface",
                    SDL_GetError());
        surface = optimized_surface;
    }
    else {
        SDL_RWops* rwops = SDL_RWFromFile(filename.c_str(), "rb");
        if (!rwops)
            throw SDLException("Error al cargar rwops", SDL_GetError());
        surface = IMG_LoadPNG_RW(rwops);
        if (!surface) {
            SDLException("Error al convertir rw a png", SDL_GetError());
            SDL_FreeRW(rwops);
        }
        SDL_FreeRW(rwops);
    }
}


Surface::~Surface() {
    SDL_FreeSurface(surface);
}

SDL_Surface* Surface::getRenderableSurface() {
    return surface;
}
