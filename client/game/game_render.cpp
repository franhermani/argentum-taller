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

GameRender::GameRender(const int screenWidth, const int screenHeight) :
                       screenWidth(screenWidth), screenHeight(screenHeight),
                       window(screenWidth, screenHeight) {
    init();
    loadSurfacePaths();
}

GameRender::~GameRender() {
    for (auto const& surface : terrainSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : npcSurfacesMap) {
        delete surface.second;
    }
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

void GameRender::createNecessaryTerrains(std::vector<std::vector<Terrain>>& matrix) {
    for (int i=0; i < blocksHeight; i++) {
        for(int j=0; j < blocksWidth; j++){
            if (terrainSurfacesMap.find(matrix[i][j]) == terrainSurfacesMap.end()) {
                if (terrainSurfacesPaths.find(matrix[i][j]) == terrainSurfacesPaths.end()) {
                    continue;
                }
                Surface *surface = new Surface(terrainSurfacesPaths[matrix[i][j]], window);
                terrainSurfacesMap.insert({matrix[i][j], surface});
            }
        }
    }
}

void GameRender::renderTerrain(std::vector<std::vector<Terrain>>& matrix) {
    createNecessaryTerrains(matrix);
    window.renderTerrain(matrix, terrainSurfacesMap);
    window.UpdateWindowSurface();
}


void GameRender::createNecessaryNpcs(std::vector<npc_pos>& npc_positions) {
    for(auto& elem:npc_positions) {
        if (npcSurfacesMap.find(elem.npc_name) == npcSurfacesMap.end()) {
            if (npcSurfacesPaths.find(elem.npc_name) == npcSurfacesPaths.end()) {
                continue;
            }
            Surface* surface = new Surface(npcSurfacesPaths[elem.npc_name], window);
            npcSurfacesMap.insert({elem.npc_name, surface});
        }
    }
}

void GameRender::renderNpcs(std::vector<npc_pos>& npc_positions) {
    // recorro vector y renderizo con su surface correspondiente en el mapa
    createNecessaryNpcs(npc_positions);
    for (auto it = std::begin(npc_positions);
    it != std::end(npc_positions); ++it) {
        window.renderNpc(it->x, it->y, npcSurfacesMap.at(it->npc_name));
    }
    window.UpdateWindowSurface();

}

void GameRender::render(std::vector<std::vector<Terrain>>& matrix,
        std::vector<npc_pos>& npc_positions) {
    //renderizamos piso y npcs
    renderTerrain(matrix);
    renderNpcs(npc_positions);
    window.UpdateWindowSurface();
}


void GameRender::loadSurfacePaths() {
    terrainSurfacesPaths = {{TERRAIN_WATER, "../client/resources/images/24082.png"},
                            {TERRAIN_LAND, "../client/resources/images/24086.png"},
                            {TERRAIN_GRASS, "../client/resources/images/24083.png"},
                            {TERRAIN_SAND, "../client/resources/images/24086.png"},
                            {TERRAIN_STONE, "../client/resources/images/12013.png"},
                            {TERRAIN_WALL, "../client/resources/images/12017.png"},
                            {TERRAIN_OUT_OF_BOUNDARIES, "../client/resources/images/12050.png"}};
    npcSurfacesPaths = {{WARRIOR_UP, "../client/resources/images/tipito_sube.png"},
                        {WARRIOR_DOWN, "../client/resources/images/tipito_baja.png"},
                        {WARRIOR_LEFT, "../client/resources/images/tipito_izq.png"},
                        {WARRIOR_RIGHT, "../client/resources/images/tipito_der.png"},
                        {SKELETON_UP, "../client/resources/images/esqueleto_sube.png"},
                        {SKELETON_DOWN, "../client/resources/images/esqueleto_baja.png"},
                        {SKELETON_LEFT, "../client/resources/images/esqueleto_izq.png"},
                        {SKELETON_RIGHT, "../client/resources/images/esqueleto_der.png"}};
}

void GameRender::setTilesSize(int width,int height) {
    blocksWidth = width;
    blocksHeight = height;
    window.setTilesSize(width,height);
}