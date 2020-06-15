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

    //TODO sacar esto de aca, recibir como parametro
    blocks_width = 20;
    blocks_height = 30;

    //inicializo la matriz, llamar a otra funcion
    matrix.resize(blocks_height);
    for (int i=0; i < blocks_height; i++) {
        std::vector<Terrain> row;
        row.resize(blocks_width);
        matrix.push_back(row);
        for (int j=0; j < blocks_width; j++) {
            matrix[i].push_back(TERRAIN_LAND);
        }
    }
    matrix[0][0] = TERRAIN_WATER;
    matrix[19][19] = TERRAIN_WATER;
    matrix[10][10] = TERRAIN_WATER;
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
SDL_Surface* SDLWindow::getSurface() const {
    return SDL_GetWindowSurface(window);
}
SDL_PixelFormat* SDLWindow::getSurfaceFormat() const {
    return SDL_GetWindowSurface(window)->format;
}

void SDLWindow::stampSurface(Surface& surface, Area& area) {
    SDL_Rect rect;
    rect.x = area.getX();
    rect.y = area.getY();
    rect.w = area.getWidth();
    rect.h = area.getHeight();
    SDL_BlitScaled(surface.get_renderable_surface(), NULL, getSurface(), &rect);
}


void SDLWindow::render_terrain(std::map<int, SDL_Surface*> terrains_map) {
    int x = 0;
    int y = 0;
    int x_blocks_size = width / blocks_width;
    int y_blocks_size = height / blocks_height;

    for (int i=0; i < blocks_height; i++) {
        x = 0;
        for (int j=0; j < blocks_width; j++) {
            SDL_Rect stretchRect;
            stretchRect.x = x;
            stretchRect.y = y;
            stretchRect.w = x_blocks_size;
            stretchRect.h = y_blocks_size;

            if (matrix[i][j] == TERRAIN_WATER) {
                SDL_BlitScaled(terrains_map[TERRAIN_WATER], NULL, getSurface(), &stretchRect);
            }
            if (matrix[i][j] == TERRAIN_LAND) {
                SDL_BlitScaled(terrains_map[TERRAIN_LAND], NULL, getSurface(), &stretchRect);
            }
            x += x_blocks_size;
        }
        y += y_blocks_size;
    }

}



void SDLWindow::UpdateWindowSurface() {
    SDL_UpdateWindowSurface(window);
}