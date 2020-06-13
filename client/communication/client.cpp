#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "client.h"
#include "../sdl/window.h"
#include "../sdl/texture.h"
#include "vector"
#include <SDL2/SDL_image.h>


Client::Client(const char *host, const char *port) :
keepPlaying(true) {
    connectionHandler = new ConnectionHandler(host, port);
}

Client::~Client() {
    delete connectionHandler;
}

void Client::connectToServer() {
    connectionHandler->start();
}

// TODO: ver cuando llamar a este metodo
void Client::disconnectFromServer() {
    connectionHandler->stop();
}


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed image
SDL_Surface* gStretchedSurface = NULL;
SDL_Surface* gStretchedSurface_2 = NULL;
SDL_Surface* guerrero_sube = NULL;
SDL_Surface* guerrero_baja = NULL;
SDL_Surface* guerrero_der = NULL;
SDL_Surface* guerrero_izq = NULL;

//gHelloWorld = SDL_LoadBMP( "/home/martinrosas/taller/taller-tp4/resources/images/hello_world.bmp" );
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load stretching surface
    gStretchedSurface = loadSurface( "/home/martinrosas/taller/taller-tp4/resources/images/24083.png" );
    gStretchedSurface_2 = loadSurface( "/home/martinrosas/taller/taller-tp4/resources/images/24082.png" );
    guerrero_sube = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_sube.png");
    guerrero_baja = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_baja.png");
    guerrero_izq = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_izq.png");
    guerrero_der = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_der.png");

    if( gStretchedSurface == NULL )
    {
        printf( "Failed to load stretching image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded image
    SDL_FreeSurface( gStretchedSurface );
    gStretchedSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

void render_background() {
    
}

void Client::render_map() {

    try {
        SDLWindow window(SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Surface* ScreenSurface = window.getSurface();
        //Start up SDL and create window
        if( !init() )
        {
            printf( "Failed to initialize!\n" );
        }
        else {
            //Load media
            if (!loadMedia()) {
                printf("Failed to load media!\n");
            } else {
                //Main loop flag


                //Apply the image stretched
                int x = 0;
                int y = 0;
                int blocks = 20;
                int x_blocks_size = SCREEN_WIDTH / blocks;
                int y_blocks_size = SCREEN_HEIGHT / blocks;
                for (int i = 0; i < blocks; i++) {
                    x = 0;
                    for (int j = 0; j < blocks; j++) {
                        SDL_Rect stretchRect;
                        stretchRect.x = x;
                        stretchRect.y = y;
                        stretchRect.w = x_blocks_size;
                        stretchRect.h = y_blocks_size;
                        SDL_BlitScaled(gStretchedSurface, NULL, ScreenSurface, &stretchRect);
                        SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
                        x += x_blocks_size;
                        std::cout << "itero x= " << x << "y= " << y << "\n";
                    }
                    y += y_blocks_size;
                }
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = 40;
                stretchRect.h = 40;
                SDL_BlitScaled(gStretchedSurface_2, NULL, ScreenSurface, &stretchRect);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
                window.UpdateWindowSurface();
            }

            //SDLTexture im("/home/martinrosas/taller/taller-tp4/resources/images/guerrero.jpg", window);

            Area srcArea(0, 0, 300, 300);
            bool running = true;
            int x = 100;
            int y = 150;
            SDL_Rect stretchRect;
            stretchRect.x = x;
            stretchRect.y = y;
            stretchRect.w = 22;
            stretchRect.h = 47;
            SDL_BlitScaled(guerrero_baja, NULL, ScreenSurface, &stretchRect);
            SDL_Surface* current_warrior;
            current_warrior = guerrero_baja;
            while (running) {
                SDL_Event event;
                //Area destArea(x, y, 300, 300);
                //window.fill();
                //im.render(srcArea, destArea);
                stretchRect.x = x;
                stretchRect.y = y;
                stretchRect.w = 22;
                stretchRect.h = 47;
                SDL_BlitScaled(current_warrior, NULL, ScreenSurface, &stretchRect);
                SDL_WaitEvent(&event);
                switch (event.type) {
                    case SDL_KEYDOWN: {
                        auto &keyEvent = (SDL_KeyboardEvent &) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                x -= 10;
                                current_warrior = guerrero_izq;
                                break;
                            case SDLK_RIGHT:
                                x += 10;
                                current_warrior = guerrero_der;
                                break;
                            case SDLK_UP:
                                y -= 10;
                                current_warrior = guerrero_sube;
                                break;
                            case SDLK_DOWN:
                                y += 10;
                                current_warrior = guerrero_baja;
                                break;
                        }
                    } // Fin KEY_DOWN
                        break;
                    case SDL_MOUSEMOTION:
                        std::cout << "Oh! Mouse" << std::endl;
                        break;
                    case SDL_QUIT:
                        std::cout << "Quit :(" << std::endl;
                        running = false;
                        break;
                }

                //window.render();
                window.UpdateWindowSurface();

            }

        }
        //SDL_Delay(10000);
        //Free resources and close SDL
        close();



        /*
        //The window we'll be rendering to
        SDL_Window* window = NULL;
        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );

        //Fill the surface white
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

        //Update the surface
        SDL_UpdateWindowSurface( window );

        //Wait two seconds
        SDL_Delay( 2000 );
        //Destroy window
        SDL_DestroyWindow( window );

        //Quit SDL subsystems
        SDL_Quit();
        */



        /*SDLWindow window(100, 100);
        window.render();
        while(true) {
            window.fill();



            SDL_Event event;
            SDL_WaitEvent(&event);
            if (event.type == SDL_QUIT) {
                    std::cout << "Quit :(" << std::endl;
                    break;
            }
        }
         */

        //window.fill();
        //SDLTexture im("../resources/images/24083.jpg", window);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Client::play() {
    // TODO: esto es de prueba
    try {
        SDLWindow window(800, 600);
        window.fill();
        // Usar factory
        SDLTexture im("../resources/images/guerrero.jpg", window);
        Area srcArea(0, 0, 300, 300);
        bool running = true;
        int x = 100;
        int y = 150;
        while (running) {
            SDL_Event event;
            Area destArea(x, y, 300, 300);
            window.fill();
            im.render(srcArea, destArea);
            SDL_WaitEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN: {
                    auto& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            x -= 10;
                            break;
                        case SDLK_RIGHT:
                            x += 10;
                            break;
                        case SDLK_UP:
                            y -= 10;
                            break;
                        case SDLK_DOWN:
                            y += 10;
                            break;
                    }
                } // Fin KEY_DOWN
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    std::cout << "Quit :(" << std::endl;
                    running = false;
                    break;
            }
            window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
