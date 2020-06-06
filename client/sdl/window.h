#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

class SDL_Window;
class SDL_Renderer;

class SDLWindow {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    // Constructor
    SDLWindow(const int width, const int height);

    // Constructor y asignacion por copia deshabilitados
    SDLWindow(const SDLWindow&) = delete;
    SDLWindow& operator=(const SDLWindow&) = delete;

    // Destructor
    ~SDLWindow();

    // Colorea la pantalla segun el codigo RGB recibido
    void fill(const int r = 0, const int g = 0, const int b = 0,
              const int alpha = 255);

    // Renderiza la pantalla
    void render();

    // Devuelve el renderer
    SDL_Renderer* getRenderer() const;
};

#endif // SDL_WINDOW_H
