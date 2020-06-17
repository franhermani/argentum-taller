#include <SDL2/SDL.h>
#include "game_render.h"
#include <iostream>
#include <exception>
#include <unistd.h>
#include "../client.h"
#include "../sdl/texture.h"
#include "vector"
#include "map"
#include "../sdl/window.h"

GameRender::GameRender(const int screenWidth, const int screenHeight,
                       const int blocksWidth, const int blocksHeight) :
                       screenWidth(screenWidth), screenHeight(screenHeight),
                       blocksWidth(blocksWidth), blocksHeight(blocksHeight),
                       window(screenWidth, screenHeight) {
    init();


    Surface* land = new Surface("../client/resources/images/24083.png", window);
    Surface* water = new Surface("../client/resources/images/24082.png", window);
    terrainSurfacesMap.insert({TERRAIN_WATER, water});
    terrainSurfacesMap.insert({TERRAIN_LAND, land});

    //ESTO LO VAMOS A SACAR AFUERA Y EL MAPA VA A SER UN ATRIBUTO DE GAME RENDER
    Surface* warrior_up = new Surface(
            "../client/resources/images/tipito_sube.png", window);
    Surface* warrior_down = new Surface(
            "../client/resources/images/tipito_baja.png", window);
    Surface* warrior_left = new Surface(
            "../client/resources/images/tipito_izq.png", window);
    Surface* warrior_right = new Surface(
            "../client/resources/images/tipito_der.png", window);
    Surface* skeleton_up = new Surface(
            "../client/resources/images/esqueleto_sube.png", window);
    Surface* skeleton_down = new Surface(
            "../client/resources/images/esqueleto_baja.png", window);
    Surface* skeleton_left = new Surface(
            "../client/resources/images/esqueleto_izq.png", window);
    Surface* skeleton_right = new Surface(
            "../client/resources/images/esqueleto_der.png", window);
    npcSurfacesMap.insert({WARRIOR_UP, warrior_up});
    npcSurfacesMap.insert({WARRIOR_DOWN, warrior_down});
    npcSurfacesMap.insert({WARRIOR_LEFT, warrior_left});
    npcSurfacesMap.insert({WARRIOR_RIGHT, warrior_right});
    npcSurfacesMap.insert({SKELETON_UP, skeleton_up});
    npcSurfacesMap.insert({SKELETON_DOWN, skeleton_down});
    npcSurfacesMap.insert({SKELETON_LEFT, skeleton_left});
    npcSurfacesMap.insert({SKELETON_RIGHT, skeleton_right});

}

GameRender::~GameRender() {
    SDL_Quit();
}

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
    window.renderTerrain(matrix, terrainSurfacesMap);
}

void GameRender::renderNpcs(std::vector<npc_pos>& npc_positions) {
    // recorro vector y renderizo con su surface correspondiente en el mapa
    for (auto it = std::begin(npc_positions);
    it != std::end(npc_positions); ++it) {
        window.renderNpc(it->x, it->y, npcSurfacesMap.at(it->npc_name));
    }
}

void GameRender::render(std::vector<Terrain>& received_terrain,
        std::vector<npc_pos>& npc_positions) {
    // inicializamos matriz de pisos a patir del vector recibido
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
