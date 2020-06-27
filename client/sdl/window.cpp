#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "window.h"
#include "exception.h"

SDLWindow::SDLWindow(const int screenWidth, const int screenHeight):
                screenHeight(screenHeight), screenWidth(screenWidth){
    int s;
    if ((s = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)))
        throw SDLException("Error al inicializar SDL", SDL_GetError());

    if ((s = SDL_CreateWindowAndRenderer(screenWidth, screenHeight,
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
    SDL_BlitScaled(surface.getRenderableSurface(), NULL, getSurface(), &rect);
}

void SDLWindow::renderNpc(int x, int y, Surface* character_surface) {
    SDL_Rect stretchRect;
    stretchRect.x = getXPixelPos(x);
    stretchRect.y = getYPixelPos(y);
    stretchRect.w = xWidthTileSize;
    stretchRect.h = yHeightTileSize;
    SDL_BlitScaled(character_surface->getRenderableSurface(), NULL,
            getSurface(), &stretchRect);
}

void SDLWindow::renderTerrain(std::vector<std::vector<Terrain>>& matrix,
                              std::map<Terrain, Surface*>& surfaces_map) {
    int height_size = matrix.size();
    int width_size = matrix[0].size();
    for (int y=0; y < height_size; y++) {
        for (int x=0; x < width_size; x++) {
            SDL_Rect stretchRect;
            stretchRect.x = getXPixelPos(x);
            stretchRect.y = getYPixelPos(y);
            stretchRect.w = xWidthTileSize;
            stretchRect.h = yHeightTileSize;
            /*if (debug) {
                std::cout << "Intento de estampar el terrain con valor: "
                        << matrix[y][x] << "\n";
                std::cout << "En los indices y:"
                        << y << " x:" << x << "\n";
                std::cout << "Esta en el mapa de superficies? "
                <<(surfaces_map.find(matrix[y][x]) != surfaces_map.end())
                << "\n";
                std::cout << "lo meto en este pixel x" << stretchRect.x
                            << " y este pixel y " << stretchRect.y
                            << "de este ancho " << stretchRect.w
                            << "y este alto " << stretchRect.h << "\n";
            }*/
            if (surfaces_map.find(matrix[y][x]) != surfaces_map.end()) {
                SDL_BlitScaled(surfaces_map.at(matrix[y][x])->
                        getRenderableSurface(), NULL,
                        getSurface(), &stretchRect);
            } else {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_WATER)->
                        getRenderableSurface(), NULL,
                        getSurface(), &stretchRect);
            }
        }
    }
}

int SDLWindow::getXPixelPos(int x_tile_position) {
    return frame_x_pixel_begin+x_tile_position*xWidthTileSize;
}
int SDLWindow::getYPixelPos(int y_tile_position) {
    return frame_y_pixel_begin+y_tile_position*yHeightTileSize;
}


void SDLWindow::UpdateWindowSurface() {
    SDL_UpdateWindowSurface(window);
}

void SDLWindow::setTilesSize(int tileWidth, int tileHeight) {
    numberOfTilesInWidth = tileWidth;
    numberOfTilesInHeight = tileHeight;
    frame_x_pixel_begin = screenWidth/50;
    frame_x_pixel_end = (screenWidth/4)*3;
    frame_y_pixel_begin = screenHeight/5;
    frame_y_pixel_end = (screenHeight/100)*95;
    xWidthTileSize =  (frame_x_pixel_end-frame_x_pixel_begin)/ numberOfTilesInWidth;
    yHeightTileSize = (frame_y_pixel_end-frame_y_pixel_begin) / numberOfTilesInHeight;

    std::cout << "esto es frame x begin " << frame_x_pixel_begin << "esto es end " << frame_x_pixel_end;
    std::cout << "esto es frame y begin " << frame_y_pixel_begin << "esto es end " << frame_y_pixel_end;


    Surface* surface = new Surface("../client/resources/images/game_frame.jpeg", *this);

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = screenWidth;
    stretchRect.h = screenHeight;
    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}
