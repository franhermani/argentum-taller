
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



int GameRender::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
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

    //recorro vector y renderizo con su surface correspondiente en el mapa
    for(std::vector<npc_pos>::iterator it = std::begin(npc_positions); it != std::end(npc_positions); ++it) {
        window.render_character(it->x, it->y, npc_surfaces_map.at(it->npc_name));
    }


}


void GameRender::play(std::vector<terrain>& received_terrain, std::vector<npc_pos>& npc_positions) {

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
    //renderizo piso y npcs
    render_terrain(matrix);
    render_npcs(npc_positions);
    window.UpdateWindowSurface();

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