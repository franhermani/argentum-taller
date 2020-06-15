
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


void GameRender::render_terrain(std::vector<std::vector<terrain>>& matrix) {
    //ESTO LO VAMOS A SACAR AFUERA Y EL MAPA VA A SER UN ATRIBUTO DE GAME RENDER
    Surface land = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24083.png", window);
    Surface water = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24082.png", window);
    std::map<terrain, Surface&> terrain_surfaces_map;
    terrain_surfaces_map.insert({TERRAIN_WATER, water});
    terrain_surfaces_map.insert({TERRAIN_LAND, land});

    window.render_terrain(matrix, terrain_surfaces_map);
    window.UpdateWindowSurface();
}

void GameRender::render_npcs(std::vector<npc_pos>& npc_positions) {
    //ESTO LO VAMOS A SACAR AFUERA Y EL MAPA VA A SER UN ATRIBUTO DE GAME RENDER
    Surface warrior_up = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_sube.png", window);
    Surface warrior_down = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_baja.png", window);
    Surface warrior_left = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_izq.png", window);
    Surface warrior_right = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_der.png", window);
    Surface skeleton_up = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_sube.png", window);
    Surface skeleton_down = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_baja.png", window);
    Surface skeleton_left = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_izq.png", window);
    Surface skeleton_right = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_der.png", window);
    std::map<npc, Surface&> npc_surfaces_map;
    npc_surfaces_map.insert({WARRIOR_UP, warrior_up});
    npc_surfaces_map.insert({WARRIOR_DOWN, warrior_down});
    npc_surfaces_map.insert({WARRIOR_LEFT, warrior_left});
    npc_surfaces_map.insert({WARRIOR_RIGHT, warrior_right});
    npc_surfaces_map.insert({SKELETON_UP, skeleton_up});
    npc_surfaces_map.insert({SKELETON_DOWN, skeleton_down});
    npc_surfaces_map.insert({SKELETON_LEFT, skeleton_left});
    npc_surfaces_map.insert({SKELETON_RIGHT, skeleton_right});
    window.render_character(0, 0, npc_surfaces_map.at(WARRIOR_RIGHT));
    window.render_character(5, 5, npc_surfaces_map.at(SKELETON_UP));
/*
    for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
        window.render_character(it->x, it->y, npc_surfaces_map.at(it->npc_name));
    }
*/
    window.UpdateWindowSurface();

}


void GameRender::play() {
    init();
    surface = window.getSurface();
    window.UpdateWindowSurface();

    //ESTO ME LO
    //VECTOR DE TERRENOS QUE RECIBIRIAMOS POR SOCKET
    std::vector<terrain> received_terrain;
    for (int i=0; i<blocksHeight*blocksWidth; i++) {
        received_terrain.push_back(TERRAIN_LAND);
    }
    received_terrain[10] = TERRAIN_WATER;

    //INCIIALIZO MATRIZ DE PISOS CON EL VECTOR RECIBIDO
    std::vector<std::vector<terrain>> matrix;
    matrix.resize(blocksHeight);
    int current_vec_index = 0;
    for (int i=0; i < blocksHeight; i++) {
        std::vector<terrain> row;
        row.resize(blocksWidth);
        matrix.push_back(row);
        for (int j=0; j < blocksWidth; j++) {
            matrix[i].push_back(received_terrain[current_vec_index]);
            ++current_vec_index;
        }
    }
    render_terrain(matrix);

/*
    Surface warrior_up = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_sube.png", window);
    Surface warrior_down = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_baja.png", window);
    Surface warrior_left = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_izq.png", window);
    Surface warrior_right = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_der.png", window);
    Surface skeleton_up = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_sube.png", window);
    Surface skeleton_down = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_baja.png", window);
    Surface skeleton_left = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_izq.png", window);
    Surface skeleton_right = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_der.png", window);
    std::map<npc, Surface&> npc_surfaces_map;
    npc_surfaces_map.insert({WARRIOR_UP, warrior_up});
    npc_surfaces_map.insert({WARRIOR_DOWN, warrior_down});
    npc_surfaces_map.insert({WARRIOR_LEFT, warrior_left});
    npc_surfaces_map.insert({WARRIOR_RIGHT, warrior_right});
    npc_surfaces_map.insert({SKELETON_UP, skeleton_up});
    npc_surfaces_map.insert({SKELETON_DOWN, skeleton_down});
    npc_surfaces_map.insert({SKELETON_LEFT, skeleton_left});
    npc_surfaces_map.insert({SKELETON_RIGHT, skeleton_right});

    window.render_character(0, 0, npc_surfaces_map.at(WARRIOR_RIGHT));
    window.render_character(5, 5, npc_surfaces_map.at(SKELETON_UP));
    window.UpdateWindowSurface();
*/

    //VECTOR DE CHARACTERS QUE RECIBIRIAMOS POR SOCKET
/*    struct npc_pos {
        int x;
        int y;
        npc npc_name;
    };*/
    std::vector<npc_pos> npc_positions;
    render_npcs(npc_positions);
    /*
    npc_pos npc_1 = {0, 0, WARRIOR_RIGHT};
    npc_pos npc_2 = {0, 10, SKELETON_DOWN};
    npc_positions.push_back(npc_1);
    npc_positions.push_back(npc_2);
    for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
        window.render_character(it->x, it->y, npc_surfaces_map.at(it->npc_name));
    }

    //dan 10 pasos a la derecha y se va renderizando
    for (int i=0; i<10; i++) {
        window.render_terrain(matrix, terrain_surfaces_map);
        for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
            window.render_character(it->x+i, it->y, npc_surfaces_map.at(it->npc_name));
        }                window.UpdateWindowSurface();
        usleep(500000);
    }
    */




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
GameRender::GameRender(const int screenWidth, const int screenHeight,
        const int blocksWidth, const int blocksHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight),
        blocksWidth(blocksWidth), blocksHeight(blocksHeight), window(screenWidth, screenHeight) {
    //Surface land = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24083.png", window);
    //Surface water = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24082.png", window);
    //terrain_surfaces_map.insert({TERRAIN_WATER, std::move(water)});
    //terrain_surfaces_map.insert({TERRAIN_LAND, std::move(land)});
    //cheqeuar aca tema copias std move
}
GameRender::~GameRender() {}