#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "client.h"
#include "../sdl/window.h"
#include "../sdl/texture.h"
#include "vector"
#include "map"


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
SDL_Surface* skeleton_sube = NULL;
SDL_Surface* skeleton_baja = NULL;
SDL_Surface* skeleton_der = NULL;
SDL_Surface* skeleton_izq = NULL;
std::map<int, SDL_Surface*> terrains_map;
std::map<int, SDL_Surface*> warriors_map;
std::map<int, SDL_Surface*> skeleton_map;

enum Terrain {
    TERRAIN_GRASS,
    TERRAIN_LAND,
    TERRAIN_SAND,
    TERRAIN_STONE,
    TERRAIN_WALL,
    TERRAIN_WATER,
};
enum Warrior {
    WARRIOR_UP,
    WARRIOR_DOWN,
    WARRIOR_RIGHT,
    WARRIOR_LEFT
};
enum Skeleton {
        SKELETON_UP,
        SKELETON_DOWN,
        SKELETON_RIGHT,
        SKELETON_LEFT
};


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

    skeleton_sube = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_sube.png");
    skeleton_baja = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_baja.png");
    skeleton_izq = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_izq.png");
    skeleton_der = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_der.png");


    terrains_map[TERRAIN_WATER] = gStretchedSurface_2;
    terrains_map[TERRAIN_LAND] = gStretchedSurface;

    warriors_map[WARRIOR_UP] = guerrero_sube;
    warriors_map[WARRIOR_DOWN] = guerrero_baja;
    warriors_map[WARRIOR_LEFT] = guerrero_izq;
    warriors_map[WARRIOR_RIGHT] = guerrero_der;


    skeleton_map[SKELETON_UP] = skeleton_sube;
    skeleton_map[SKELETON_DOWN] = skeleton_baja;
    skeleton_map[SKELETON_LEFT] = skeleton_izq;
    skeleton_map[SKELETON_RIGHT] = skeleton_der;


    warriors_map[0] = guerrero_sube;
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




void Client::render_terrain(SDL_Surface* ScreenSurface) {

    //supongamos que es cuadrada, sino hay que dividir en blocks de width y height
    const int blocks = 20;
    Terrain matrix[blocks][blocks]{};
    for (int i=0; i < blocks; i++) {
        for (int j=0; j < blocks; j++) {
            matrix[i][j] = TERRAIN_LAND;
        }
    }
    matrix[0][0] = TERRAIN_WATER;
    matrix[19][19] = TERRAIN_WATER;
    matrix[10][10] = TERRAIN_WATER;

    int x = 0;
    int y = 0;
    int x_blocks_size = SCREEN_WIDTH / blocks;
    int y_blocks_size = SCREEN_HEIGHT / blocks;

    for (int i=0; i < x_blocks_size; i++) {
        x = 0;
        for (int j=0; j<y_blocks_size; j++) {
            SDL_Rect stretchRect;
            stretchRect.x = x;
            stretchRect.y = y;
            stretchRect.w = x_blocks_size;
            stretchRect.h = y_blocks_size;

            if (matrix[i][j] == TERRAIN_WATER) {
                SDL_BlitScaled(terrains_map[TERRAIN_WATER], NULL, ScreenSurface, &stretchRect);
            }
            if (matrix[i][j] == TERRAIN_LAND) {
                SDL_BlitScaled(terrains_map[TERRAIN_LAND], NULL, ScreenSurface, &stretchRect);
            }
            x += x_blocks_size;
        }
        y += y_blocks_size;
    }

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

                render_terrain(ScreenSurface);
                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
                window.UpdateWindowSurface();
            }
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
                stretchRect.x = x;
                stretchRect.y = y;
                stretchRect.w = 22;
                stretchRect.h = 47;
                render_terrain(ScreenSurface);
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
