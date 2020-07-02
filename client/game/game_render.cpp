#include <SDL2/SDL.h>
#include "game_render.h"
#include <iostream>
#include <exception>
#include <chrono>
#include <unistd.h>
#include "../client.h"
#include "../sdl/texture.h"
#include "vector"
#include "map"
#include "../sdl/window.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"

GameRender::GameRender(const int screenWidth, const int screenHeight,
        MapMonitor& mapMonitor) :
                       screenWidth(screenWidth), screenHeight(screenHeight),
                       mapMonitor(mapMonitor),
                       window(screenWidth, screenHeight) {
    init();
    loadSurfacePaths();
}

GameRender::~GameRender() {
    for (auto const& surface : terrainSurfacesMap) {
        delete surface.second;
    }
    //TODO DELETE DE LAS OTRAS SURFACES!!!!!!!!
//    for (auto const& surface : creatureSurfacesMap) {
//        delete surface.second;
//    }
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

Surface* GameRender::createGameFrameSurface(){
    return new Surface("../client/resources/images/game_frame.jpeg", window, 0);
}

void GameRender::createNecessaryTerrains(
        std::vector<std::vector<Terrain>>& matrix) {
    int height_size = matrix.size();
    if (height_size < 1) return;
    int width_size = matrix[0].size();
    for (int i=0; i < height_size; i++) {
        for (int j=0; j < width_size; j++){
            if (terrainSurfacesMap.find(matrix[i][j])
                    == terrainSurfacesMap.end()) {
                if (terrainSurfacesPaths.find(matrix[i][j])
                        == terrainSurfacesPaths.end()) {
                    continue;
                }
                Surface *surface = new Surface(
                        terrainSurfacesPaths[matrix[i][j]], window, 0);
                terrainSurfacesMap.insert({matrix[i][j], surface});
            }
        }
    }
}


void GameRender::renderTerrain(std::vector<std::vector<Terrain>> matrix) {
    createNecessaryTerrains(matrix);
    window.renderTerrain(matrix, terrainSurfacesMap);
}

void GameRender::createNecessaryPlayers(std::vector<player_t>& players) {
    for (auto& player:players) {
        int race = player.race_type;
        int orientation = player.orientation;
        if (playerSurfacesMap[race].find(orientation)
                == playerSurfacesMap[race].end()) {
            if (playerSurfacesPaths[race].find(orientation)
                    == playerSurfacesPaths[race].end()) {
                continue;
            }
            Surface* surface = new Surface(
                    playerSurfacesPaths[race][orientation], window, 1);
            playerSurfacesMap[race].insert({orientation, surface});
        }
    }
}

void GameRender::renderPlayers(std::vector<player_t>& players) {
    createNecessaryPlayers(players);
    for (auto it = std::begin(players);
         it != std::end(players); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                playerSurfacesMap[it->race_type][it->orientation]);
    }
}

void GameRender::createNecessaryCreatures(std::vector<creature_t>& creatures) {
    for (auto& creature:creatures) {
        int type = creature.type;
        int orientation = creature.orientation;
        if (creatureSurfacesMap[type].find(orientation)
            == creatureSurfacesMap[type].end()) {
            if (creatureSurfacesPaths[type].find(orientation)
                == creatureSurfacesPaths[type].end()) {
                continue;
            }
            Surface* surface = new Surface(
                    creatureSurfacesPaths[type][orientation], window, 1);
            creatureSurfacesMap[type].insert({orientation, surface});
        }
    }
}


void GameRender::renderCreatures(std::vector<creature_t>& creatures) {
    createNecessaryCreatures(creatures);
    for (auto it = std::begin(creatures);
         it != std::end(creatures); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                         creatureSurfacesMap[it->type][it->orientation]);
    }
}


void GameRender::createNecessaryNpcs(std::vector<npc_t>& npcs) {
    for (auto& npc:npcs) {
        int type = npc.type;
        int orientation = npc.orientation;
        if (npcSurfacesMap[type].find(orientation)
            == npcSurfacesMap[type].end()) {
            if (npcSurfacesPaths[type].find(orientation)
                == npcSurfacesPaths[type].end()) {
                continue;
            }
            Surface* surface = new Surface(
                    npcSurfacesPaths[type][orientation], window, 1);
            npcSurfacesMap[type].insert({orientation, surface});
        }
    }
}

void GameRender::renderNpcs(std::vector<npc_t>& npcs) {
    createNecessaryNpcs(npcs);
    for (auto it = std::begin(npcs);
         it != std::end(npcs); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                         npcSurfacesMap[it->type][it->orientation]);
    }
}



void GameRender::loadSurfacePaths() {
    //PISOS
    terrainSurfacesPaths = {
            {TERRAIN_WATER, "../client/resources/images/24082.png"},
            {TERRAIN_LAND, "../client/resources/images/24086.png"},
            {TERRAIN_GRASS, "../client/resources/images/24083.png"},
            {TERRAIN_SAND, "../client/resources/images/24086.png"},
            {TERRAIN_STONE, "../client/resources/images/12013.png"},
            {TERRAIN_WALL, "../client/resources/images/12017.png"},
            {TERRAIN_OUT_OF_BOUNDARIES,
             "../client/resources/images/12050.png"}};

    //CRIATURAS
    std::map<int, std::string> skeleton_orientations = {
            {UP, "../client/resources/images/skeleton_up_t.png"},
            {DOWN, "../client/resources/images/skeleton_down_t.png"},
            {LEFT, "../client/resources/images/skeleton_left_t.png"},
            {RIGHT, "../client/resources/images/skeleton_right_t.png"}
    };
    std::map<int, std::string> goblin_orientations = {
            {UP, "../client/resources/images/goblin_up_t.png"},
            {DOWN, "../client/resources/images/goblin_down_t.png"},
            {LEFT, "../client/resources/images/goblin_left_t.png"},
            {RIGHT, "../client/resources/images/goblin_right_t.png"}
    };

    std::map<int, std::string> zombie_orientations = {
            {UP, "../client/resources/images/zombie_up_t.png"},
            {DOWN, "../client/resources/images/zombie_down_t.png"},
            {LEFT, "../client/resources/images/zombie_left_t.png"},
            {RIGHT, "../client/resources/images/zombie_right_t.png"}
    };


    npcSurfacesPaths = {
            {SKELETON, skeleton_orientations},
            {ZOMBIE, zombie_orientations},
            {GOBLIN, goblin_orientations}
    };

    std::map<int, Surface*> skeleton_surfaces;
    std::map<int, Surface*> zombie_surfaces;
    std::map<int, Surface*> goblin_surfaces;
    npcSurfacesMap = {{SKELETON, skeleton_surfaces},
                      {ZOMBIE,   zombie_surfaces},
                      {GOBLIN,   goblin_surfaces}
    };



    //npcs
    std::map<int, std::string> banker_orientations = {
            {UP, "../client/resources/images/banker_up_t.png"},
            {DOWN, "../client/resources/images/banker_down_t.png"},
            {LEFT, "../client/resources/images/banker_left_t.png"},
            {RIGHT, "../client/resources/images/banker_right_t.png"}
    };
    std::map<int, std::string> priest_orientations = {
            {UP, "../client/resources/images/priest_up_t.png"},
            {DOWN, "../client/resources/images/priest_down_t.png"},
            {LEFT, "../client/resources/images/priest_left_t.png"},
            {RIGHT, "../client/resources/images/priest_right_t.png"}
    };
    std::map<int, std::string> merchant_orientations = {
            {UP, "../client/resources/images/merchant_up_t.png"},
            {DOWN, "../client/resources/images/merchant_down_t.png"},
            {LEFT, "../client/resources/images/merchant_left_t.png"},
            {RIGHT, "../client/resources/images/merchant_right_t.png"}
    };

    npcSurfacesPaths = {
            {PRIEST, priest_orientations},
            {MERCHANT, merchant_orientations},
            {BANKER, {banker_orientations}}
    };

    std::map<int, Surface*> priest_surfaces;
    std::map<int, Surface*> merchant_surfaces;
    std::map<int, Surface*> banker_surfaces;
    npcSurfacesMap = {{PRIEST, priest_surfaces},
                           {MERCHANT, merchant_surfaces},
                           {BANKER, banker_surfaces}
    };


    //JUGADORES

    std::map<int, std::string> human_orientations = {
            {UP, "../client/resources/images/human_up_t.png"},
            {DOWN, "../client/resources/images/human_down_t.png"},
            {LEFT, "../client/resources/images/human_left_t.png"},
            {RIGHT, "../client/resources/images/human_right_t.png"}
    };
    std::map<int, std::string> elf_orientations = {
            {UP, "../client/resources/images/elf_up_t.png"},
            {DOWN, "../client/resources/images/elf_down_t.png"},
            {LEFT, "../client/resources/images/elf_left_t.png"},
            {RIGHT, "../client/resources/images/elf_right_t.png"}
    };
    std::map<int, std::string> dwarf_orientations = {
            {UP, "../client/resources/images/dwarf_up_t.png"},
            {DOWN, "../client/resources/images/dwarf_down_t.png"},
            {LEFT, "../client/resources/images/dwarf_left_t.png"},
            {RIGHT, "../client/resources/images/dwarf_right_t.png"}
    };
    std::map<int, std::string> gnome_orientations = {
            {UP, "../client/resources/images/gnome_up_t.png"},
            {DOWN, "../client/resources/images/gnome_down_t.png"},
            {LEFT, "../client/resources/images/gnome_left_t.png"},
            {RIGHT, "../client/resources/images/gnome_right_t.png"}
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

void GameRender::run() {
    using ms = std::chrono::milliseconds;
    std::this_thread::sleep_for(ms(500));
    blocksWidth = mapMonitor.getPlayerVisionWidth();
    blocksHeight = mapMonitor.getPlayerVisionHeight();
    window.setTilesSize(blocksWidth,blocksHeight);
    window.renderGameFrame(createGameFrameSurface());

    while (keepRunning) {
        std::vector<std::vector<Terrain>> terrains = mapMonitor.getTerrains();
        renderTerrain(terrains);
        std::vector<player_t> players = mapMonitor.getRenderablePlayers();
        renderPlayers(players);
        std::vector<npc_t> npcs = mapMonitor.getRenderableNpcs();
        renderNpcs(npcs);
        //std::vector<creature_t> creatures = mapMonitor.getRenderableCreatures();
        //renderCreatures(creatures);
        window.UpdateWindowSurface();
        std::this_thread::sleep_for(ms(10));
    }
}

void GameRender::stop() {
    keepRunning = false;
}

bool GameRender::isDead()  {
    return (! isRunning);
}
