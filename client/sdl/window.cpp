#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "window.h"
#include "exception.h"

SDLWindow::SDLWindow(const int width, const int height) :
width(width), height(height) {
    int s;
    if ((s = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)))
        throw SDLException("Error al inicializar SDL", SDL_GetError());

    if ((s = SDL_CreateWindowAndRenderer(width, height,
            SDL_RENDERER_ACCELERATED, &window, &renderer)))
        throw SDLException("Error al crear la ventana", SDL_GetError());
}

SDLWindow::~SDLWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void SDLWindow::fill(const int r, const int g, const int b, const int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

void SDLWindow::render() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLWindow::getRenderer() const {
    return renderer;
}
