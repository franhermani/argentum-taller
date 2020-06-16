
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


void GameRender::renderTerrain(std::vector<std::vector<Terrain>>& matrix) {
    //ESTO LO VAMOS A SACAR AFUERA Y EL MAPA VA A SER UN ATRIBUTO DE GAME RENDER
    Surface land = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24083.png", window);
    Surface water = Surface("/home/martinrosas/taller/taller-tp4/resources/images/24082.png", window);
    std::map<Terrain, Surface&> terrain_surfaces_map;
    terrain_surfaces_map.insert({TERRAIN_WATER, water});
    terrain_surfaces_map.insert({TERRAIN_LAND, land});

    window.renderTerrain(matrix, terrain_surfaces_map);
}

void GameRender::renderNpcs(std::vector<npc_pos>& npc_positions) {
    //ESTO LO VAMOS A SACAR AFUERA Y EL MAPA VA A SER UN ATRIBUTO DE GAME RENDER
    Surface warrior_up = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_sube.png", window);
    Surface warrior_down = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_baja.png", window);
    Surface warrior_left = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_izq.png", window);
    Surface warrior_right = Surface("/home/martinrosas/taller/taller-tp4/resources/images/tipito_der.png", window);
    Surface skeleton_up = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_sube.png", window);
    Surface skeleton_down = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_baja.png", window);
    Surface skeleton_left = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_izq.png", window);
    Surface skeleton_right = Surface("/home/martinrosas/taller/taller-tp4/resources/images/esqueleto_der.png", window);
    std::map<Npc, Surface&> npc_surfaces_map;
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
        window.renderNpc(it->x, it->y, npc_surfaces_map.at(it->npc_name));
    }


}


void GameRender::play(std::vector<Terrain>& received_terrain, std::vector<npc_pos>& npc_positions) {
    //inicializamos matriz de pisos a patir del vector recibido
    std::vector<std::vector<Terrain>> matrix;
    matrix.resize(blocksHeight);
    int current_vec_index = 0;
    for (int i=0; i < blocksHeight; i++) {
        std::vector<Terrain> row;
        row.resize(blocksWidth);
        matrix.push_back(row);
        for (int j=0; j < blocksWidth; j++) {
            matrix[i].push_back(received_terrain[current_vec_index]);
            ++current_vec_index;
        }
    }
    //renderizamos piso y npcs
    renderTerrain(matrix);
    renderNpcs(npc_positions);
    window.UpdateWindowSurface();

}


GameRender::GameRender(const int screenWidth, const int screenHeight,
        const int blocksWidth, const int blocksHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight),
        blocksWidth(blocksWidth), blocksHeight(blocksHeight), window(screenWidth, screenHeight) {
    init();
}
GameRender::~GameRender() {
    SDL_Quit();
}