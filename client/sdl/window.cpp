#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "window.h"
#include "exception.h"

SDLWindow::SDLWindow(const int width, const int height): width(width), height(height){
    int s;
    if ((s = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)))
        throw SDLException("Error al inicializar SDL", SDL_GetError());

    if ((s = SDL_CreateWindowAndRenderer(width, height,
            SDL_RENDERER_ACCELERATED, &window, &renderer)))
        throw SDLException("Error al crear la ventana", SDL_GetError());

    //TODO sacar numero magico de aca, recibir como parametro
    numberOfTilesInWidth = 10;
    numberOfTilesInHeight = 10;
    xWidthTileSize = width/10;
    yHeightTileSize = height/10;
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


    for (int y=0; y < numberOfTilesInHeight; y++) {
        for (int x=0; x < numberOfTilesInWidth; x++) {
            SDL_Rect stretchRect;
            stretchRect.x = getXPixelPos(x);
            stretchRect.y = getYPixelPos(y);
            stretchRect.w = xWidthTileSize;
            stretchRect.h = yHeightTileSize;
            std::cout << "estoy intentando estampar este: " <<matrix[y][x]<<"\n";
            std::cout << "esta? " << (surfaces_map.find(matrix[y][x]) != surfaces_map.end()) << "\n";
            std::cout << "lo meto en este x" << stretchRect.x << " y este y "<< stretchRect.y << "de este ancho " <<stretchRect.w << "y este alto "<< stretchRect.h << "\n";
            if (surfaces_map.find(matrix[y][x]) != surfaces_map.end()) {
                SDL_BlitScaled(surfaces_map.at(matrix[y][x])->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            } else {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_WATER)->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            }
            /*
            //TODO SACAR TODOS ESTOS IFS
            if (matrix[y][x] == TERRAIN_WATER) {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_WATER)->
                getRenderableSurface(), NULL, getSurface(), &stretchRect);
            }
            else if (matrix[y][x] == TERRAIN_LAND) {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_LAND)->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            } else if (matrix[y][x] == TERRAIN_GRASS) {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_GRASS)->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            } else if (matrix[y][x] == TERRAIN_SAND) {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_SAND)->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            }
            else if (matrix[y][x] == TERRAIN_STONE) {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_STONE)->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            }
            else if (matrix[y][x] == TERRAIN_WALL) {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_WALL)->
                        getRenderableSurface(), NULL, getSurface(), &stretchRect);
            }
            else {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_WATER)->
                getRenderableSurface(), NULL, getSurface(), &stretchRect);
            }*/
        }
    }
}

int SDLWindow::getXPixelPos(int x_tile_position) {
    return x_tile_position*xWidthTileSize;

}
int SDLWindow::getYPixelPos(int y_tile_position) {
    return y_tile_position*yHeightTileSize;

}


void SDLWindow::UpdateWindowSurface() {
    SDL_UpdateWindowSurface(window);
}

void SDLWindow::setTilesSize(int tileWidth, int tileHeight) {
    numberOfTilesInWidth = tileWidth;
    numberOfTilesInHeight = tileHeight;
    xWidthTileSize = width / numberOfTilesInWidth;
    yHeightTileSize = height / numberOfTilesInHeight;
}