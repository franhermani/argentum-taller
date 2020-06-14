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
SDL_Surface* land = NULL;
SDL_Surface* water = NULL;
SDL_Surface* warrior_up = NULL;
SDL_Surface* warrior_down = NULL;
SDL_Surface* warrior_right = NULL;
SDL_Surface* warrior_left = NULL;
SDL_Surface* skeleton_up = NULL;
SDL_Surface* skeleton_down = NULL;
SDL_Surface* skeleton_right = NULL;
SDL_Surface* skeleton_left = NULL;
std::map<int, SDL_Surface*> terrains_map;
std::map<int, SDL_Surface*> npcs_map;
const int blocks_width = 20;
const int blocks_height = 30;


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
    land = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/24083.png" );
    water = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/24082.png" );
    warrior_up = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_sube.png");
    warrior_down = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_baja.png");
    warrior_left = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_izq.png");
    warrior_right = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_der.png");
    skeleton_up = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_sube.png");
    skeleton_down = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_baja.png");
    skeleton_left = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_izq.png");
    skeleton_right = loadSurface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_der.png");
    terrains_map[TERRAIN_WATER] = water;
    terrains_map[TERRAIN_LAND] = land;
    npcs_map[WARRIOR_UP] = warrior_up;
    npcs_map[WARRIOR_DOWN] = warrior_down;
    npcs_map[WARRIOR_LEFT] = warrior_left;
    npcs_map[WARRIOR_RIGHT] = warrior_right;
    npcs_map[SKELETON_UP] = skeleton_up;
    npcs_map[SKELETON_DOWN] = skeleton_down;
    npcs_map[SKELETON_LEFT] = skeleton_left;
    npcs_map[SKELETON_RIGHT] = skeleton_right;
    npcs_map[0] = warrior_up;
    if(land == NULL )
    {
        printf( "Failed to load stretching image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded image
    SDL_FreeSurface(land );
    land = NULL;

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

/*
void Client::render_characters(SDL_Surface* ScreenSurface, std::vector<std::vector<Terrain>> matrix) {

}*/


void Client::render_terrain(SDL_Surface* ScreenSurface, std::vector<std::vector<Terrain>> matrix) {

    int x = 0;
    int y = 0;
    int x_blocks_size = SCREEN_WIDTH / blocks_width;
    int y_blocks_size = SCREEN_HEIGHT / blocks_height;

    for (int i=0; i < blocks_height; i++) {
        x = 0;
        for (int j=0; j < blocks_width; j++) {
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
        
        std::vector<std::vector<Terrain>> matrix;
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

                render_terrain(ScreenSurface, matrix);
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
            SDL_BlitScaled(warrior_down, NULL, ScreenSurface, &stretchRect);
            SDL_Surface* current_warrior;
            current_warrior = warrior_down;
            while (running) {
                SDL_Event event;
                stretchRect.x = x;
                stretchRect.y = y;
                stretchRect.w = 22;
                stretchRect.h = 47;
                render_terrain(ScreenSurface, matrix);
                SDL_BlitScaled(current_warrior, NULL, ScreenSurface, &stretchRect);
                SDL_WaitEvent(&event);
                switch (event.type) {
                    case SDL_KEYDOWN: {
                        auto &keyEvent = (SDL_KeyboardEvent &) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                x -= 10;
                                current_warrior = warrior_left;
                                break;
                            case SDLK_RIGHT:
                                x += 10;
                                current_warrior = warrior_right;
                                break;
                            case SDLK_UP:
                                y -= 10;
                                current_warrior = warrior_up;
                                break;
                            case SDLK_DOWN:
                                y += 10;
                                current_warrior = warrior_down;
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
