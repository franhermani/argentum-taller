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
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"


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

void GameRender::renderTerrain(std::vector<std::vector<Terrain>> matrix) {
    floor = matrix;
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
    //re renderizo piso
    window.renderTerrain(floor, terrainSurfacesMap);
    // recorro vector y renderizo con su surface correspondiente en el mapa
    createNecessaryNpcs(npc_positions);
    for (auto it = std::begin(npc_positions);
    it != std::end(npc_positions); ++it) {
        window.renderNpc(it->x, it->y, npcSurfacesMap.at(it->npc_name));
    }
    window.UpdateWindowSurface();
}

void GameRender::createNecessaryPlayers(std::vector<player_t>& players) {
    for(auto& player:players) {
        int race = player.race_type;
        int orientation = player.orientation;
        if (playerSurfacesMap[race].find(orientation) == playerSurfacesMap[race].end()) {
            if (playerSurfacesPaths[race].find(orientation) == playerSurfacesPaths[race].end()) {
                continue;
            }
            Surface* surface = new Surface(playerSurfacesPaths[race][orientation], window);
            playerSurfacesMap[race].insert({orientation, surface});
        }
    }
}

void GameRender::renderPlayers(std::vector<player_t>& players) {
    window.renderTerrain(floor, terrainSurfacesMap);
    // recorro vector y renderizo con su surface correspondiente en el mapa

    createNecessaryPlayers(players);
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {
        window.renderNpc(it->pos_x, it->pos_y, playerSurfacesMap[it->race_type][it->orientation]);
    }
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

    std::map<int, std::string> human_orientations = {
            {UP, "../client/resources/images/human_up.png"},
            {DOWN, "../client/resources/images/human_down.png"},
            {LEFT, "../client/resources/images/human_left.png"},
            {RIGHT, "../client/resources/images/human_right.png"}
    };
    std::map<int, std::string> elf_orientations = {
            {UP, "../client/resources/images/elf_up.png"},
            {DOWN, "../client/resources/images/elf_down.png"},
            {LEFT, "../client/resources/images/elf_left.png"},
            {RIGHT, "../client/resources/images/elf_right.png"}
    };
    std::map<int, std::string> dwarf_orientations = {
            {UP, "../client/resources/images/dwarf_up.png"},
            {DOWN, "../client/resources/images/dwarf_down.png"},
            {LEFT, "../client/resources/images/dwarf_left.png"},
            {RIGHT, "../client/resources/images/dwarf_right.png"}
    };
    std::map<int, std::string> gnome_orientations = {
            {UP, "../client/resources/images/gnome_up.png"},
            {DOWN, "../client/resources/images/gnome_down.png"},
            {LEFT, "../client/resources/images/gnome_left.png"},
            {RIGHT, "../client/resources/images/gnome_right.png"}
    };
    playerSurfacesPaths = {
            {HUMAN, human_orientations},
            {ELF, elf_orientations},
            {DWARF, dwarf_orientations},
            {GNOME, gnome_orientations}
    };
    std::map<int, Surface*> human_surfaces;
    std::map<int, Surface*> elf_surfaces;
    std::map<int, Surface*> dwarf_surfaces;
    std::map<int, Surface*> gnome_surfaces;
    playerSurfacesMap = {{HUMAN, human_surfaces},
                           {ELF, elf_surfaces},
                           {DWARF, dwarf_surfaces},
                           {GNOME, gnome_surfaces}};

}

void GameRender::setTilesSize(int width,int height) {
    blocksWidth = width;
    blocksHeight = height;
    window.setTilesSize(width,height);
}