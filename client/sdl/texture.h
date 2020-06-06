#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include <string>
#include "window.h"
#include "area.h"

class SDL_Texture;
class SDL_Renderer;

class SDLTexture {
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    // Carga la textura
    SDL_Texture* loadTexture(const std::string& filename);

public:
    // Constructor
    SDLTexture(const std::string filename, const SDLWindow& window);

    // Destructor
    ~SDLTexture();

    // Renderiza la textura
    int render(const Area& src, const Area& dest) const;
};

#endif // SDL_TEXTURE_H
