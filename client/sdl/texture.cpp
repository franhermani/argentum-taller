#include <SDL2/SDL_image.h>
#include <string>
#include "texture.h"
#include "window.h"
#include "exception.h"

SDLTexture::SDLTexture(const std::string filename, const SDLWindow &window) :
renderer(window.getRenderer()) {
    texture = loadTexture(filename);
}

SDLTexture::~SDLTexture() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* SDLTexture::loadTexture(const std::string &filename) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, filename.c_str());

    if (! new_texture)
        throw SDLException("Error al cargar la textura", SDL_GetError());

    return new_texture;
}

int SDLTexture::render(const Area &src, const Area &dest) const {
    SDL_Rect sdl_src = {src.getX(), src.getY(),
                        src.getWidth(), src.getHeight()};

    SDL_Rect sdl_dest = {dest.getX(), dest.getY(),
                         dest.getWidth(), dest.getHeight()};

    return SDL_RenderCopy(renderer, texture, &sdl_src, &sdl_dest);
}
