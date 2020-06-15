
#include "game_render.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>
#include "client.h"
#include "../sdl/texture.h"
#include "vector"
#include "map"
#include "../sdl/window.h"


SDL_Surface* surface;

int GameRender::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //CREO VENTANA
        //window = SDLWindow(screen_width, screen_height);
    }
    return success;
}


void GameRender::play() {
    init();
    surface = window.getSurface();
    window.UpdateWindowSurface();

    //ESTO ME LO
    //VECTOR DE TERRENOS QUE RECIBIRIAMOS POR SOCKET
    std::vector<terrain> received_terrain;
    for (int i=0; i<blocks_height*blocks_width; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;

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

    Surface land = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24083.png", window);
    Surface water = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24082.png", window);
    std::map<terrain, Surface&> terrain_surfaces_map;
    std::map<npc, Surface&> npc_surfaces_map;

    terrain_surfaces_map.insert({TERRAIN_WATER, water});
    terrain_surfaces_map.insert({TERRAIN_LAND, land});
    window.render_terrain(matrix, terrain_surfaces_map);
    window.UpdateWindowSurface();





    //espero el quit
    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
    }
}






//TODO RESULUCION SE PUEDE CONSEGIUR DESDE ACA ADENTRO EN VEZ DE PASAR NUMERO MAGICO
//EMPROLIJARRRRRRRRRRRRRRRRRRRRRRRRRR antes de hacer pr
GameRender::GameRender(const int screen_width, const int screen_height,
        const int blocks_width, const int blocks_height)
        : screen_width(screen_width), screen_height(screen_height),
        blocks_width(blocks_width), blocks_height(blocks_height), window(screen_width, screen_height) {
}
GameRender::~GameRender() {}