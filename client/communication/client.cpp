#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>
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
const int SCREEN_WIDTH = 640*2;
const int SCREEN_HEIGHT = 480*2;
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
std::map<int, SDL_Surface*> terrain_surfaces_map;
std::map<int, SDL_Surface*> npc_surfaces_map;
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






void Client::render_map() {

    //VECTOR DE TERRENOS QUE RECIBIRIAMOS POR SOCKET
    std::vector<terrain> received_terrain;
    for (int i=0; i<blocks_height*blocks_width; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;


    try {
        //CREO VENTANA Y PIDO SU SUPERFICIE
        SDLWindow window(SCREEN_WIDTH, SCREEN_HEIGHT);
        //SDL_Surface* ScreenSurface = window.getSurface();


        //INCIIALIZO MATRIZ DE PISOS CON EL VECTOR RECIBIDO
        std::vector<std::vector<terrain>> matrix;
        matrix.resize(blocks_height);
        int current_vec_index = 0;
        for (int i=0; i < blocks_height; i++) {
            std::vector<terrain> row;
            row.resize(blocks_width);
            matrix.push_back(row);
            for (int j=0; j < blocks_width; j++) {
                matrix[i].push_back(received_terrain[current_vec_index]);
                ++current_vec_index;
            }
        }


                //Start up SDL and create window
        if( !init() )
        {
            printf( "Failed to initialize!\n" );
        }
        else {
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

            terrain_surfaces_map[TERRAIN_WATER] = water;
            terrain_surfaces_map[TERRAIN_LAND] = land;
            npc_surfaces_map[WARRIOR_UP] = warrior_up;
            npc_surfaces_map[WARRIOR_DOWN] = warrior_down;
            npc_surfaces_map[WARRIOR_LEFT] = warrior_left;
            npc_surfaces_map[WARRIOR_RIGHT] = warrior_right;
            npc_surfaces_map[SKELETON_UP] = skeleton_up;
            npc_surfaces_map[SKELETON_DOWN] = skeleton_down;
            npc_surfaces_map[SKELETON_LEFT] = skeleton_left;
            npc_surfaces_map[SKELETON_RIGHT] = skeleton_right;
            npc_surfaces_map[0] = warrior_up;
            if(land == NULL )
            {
                //TODO ERROR SI NO PUEDE CARGAR UNA IMAGEN
            }
            window.render_terrain(matrix, terrain_surfaces_map);

            //VECTOR DE CHARACTERS QUE RECIBIRIAMOS POR SOCKET
            struct npc_pos {
                int x;
                int y;
                npc npc_name;
            };
            std::vector<npc_pos> npc_positions;
            npc_pos npc_1 = {0, 0, WARRIOR_RIGHT};
            npc_pos npc_2 = {0, 10, SKELETON_DOWN};
            npc_positions.push_back(npc_1);
            npc_positions.push_back(npc_2);
            for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
                window.render_character(it->x, it->y, npc_surfaces_map[it->npc_name]);
            }
            window.UpdateWindowSurface();



            //dan 10 pasos a la derecha y se va renderizando
            for (int i=0; i<10; i++) {
                window.render_terrain(matrix, terrain_surfaces_map);
                for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
                    window.render_character(it->x+i, it->y, npc_surfaces_map[it->npc_name]);
                }                window.UpdateWindowSurface();
                usleep(500000);
            }



            //espero el quit
            SDL_Event event;
            while (true) {
                SDL_WaitEvent(&event);
                if (event.type == SDL_QUIT) {
                    break;
                }
            }

            /*
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
                window.render_terrain(matrix, terrain_surfaces_map);
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
             */


        }
        //SDL_Delay(10000);
        //Free resources and close SDL
        close();





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
