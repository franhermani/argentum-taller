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
#include <utility>
#include "../sdl/window.h"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"
#include "exception.h"

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


void GameRender::renderTerrain(std::vector<std::vector<Terrain>>& matrix) {
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


void GameRender::createNecessaryFloorItems(std::vector<item_t> &items) {
    for (auto& item:items) {
        int type = item.type;
        if (floorItemSurfacesMap.find(type)
            == floorItemSurfacesMap.end()) {
            if (floorItemSurfacesPaths.find(type)
                == floorItemSurfacesPaths.end()) {
                continue;
            }
            Surface* surface = new Surface(
                    floorItemSurfacesPaths[type], window, 1);
            floorItemSurfacesMap.insert({type, surface});
        }
    }
}

void GameRender::renderItems(std::vector<item_t> &items) {
    createNecessaryFloorItems(items);
    for (auto it = std::begin(items);
         it != std::end(items); ++it) {
        window.renderNpc(it->pos_x, it->pos_y,
                         floorItemSurfacesMap[it->type]);
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
    std::map<int, std::string> spider_orientations = {
            {UP, "../client/resources/images/spider_up_t.png"},
            {DOWN, "../client/resources/images/spider_down_t.png"},
            {LEFT, "../client/resources/images/spider_left_t.png"},
            {RIGHT, "../client/resources/images/spider_right_t.png"}
    };


    creatureSurfacesPaths = {
            {SKELETON, skeleton_orientations},
            {ZOMBIE, zombie_orientations},
            {GOBLIN, goblin_orientations},
            {SPIDER, spider_orientations}
    };

    std::map<int, Surface*> skeleton_surfaces;
    std::map<int, Surface*> zombie_surfaces;
    std::map<int, Surface*> goblin_surfaces;
    creatureSurfacesMap = {{SKELETON, skeleton_surfaces},
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

    floorItemSurfacesPaths = {
            {ESPADA, "../client/resources/images/espada_t.png"},
            {HACHA, "../client/resources/images/hacha_t.png"},
            {MARTILLO, "../client/resources/images/martillo_t.png"},
            {VARA_FRESNO, "../client/resources/images/vara_fresno_t.png"},
            {FLAUTA_ELFICA, "../client/resources/images/flauta_elfica_t.png"},
            {BACULO_NUDOSO, "../client/resources/images/baculo_nudoso_t.png"},
            {BACULO_ENGARZADO,
                "../client/resources/images/baculo_engarzado_t.png"},
            {ARCO_SIMPLE, "../client/resources/images/arco_simple_t.png"},
            {ARCO_COMPUESTO,
                "../client/resources/images/arco_compuesto_t.png"},
            {ARMADURA_CUERO,
                "../client/resources/images/armadura_cuero_t.png"},
            {ARMADURA_PLACAS,
                "../client/resources/images/armadura_placas_t.png"},
            {TUNICA_AZUL,
                "../client/resources/images/tunica_azul_t.png"},
            {CAPUCHA, "../client/resources/images/capucha_t.png"},
            {CASCO_HIERRO, "../client/resources/images/casco_hierro_t.png"},
            {SOMBRERO_MAGICO,
                "../client/resources/images/sombrero_magico_t.png"},
            {ESCUDO_TORTUGA,
                "../client/resources/images/escudo_tortuga_t.png"},
            {ESCUDO_HIERRO, "../client/resources/images/escudo_hierro_t.png"},
            {POCION_VIDA, "../client/resources/images/pocion_vida_t.png"},
            {POCION_MANA, "../client/resources/images/pocion_mana_t.png"},
    };
    floorItemSurfacesMap = {
            {ESPADA, new Surface(
                    "../client/resources/images/espada_t.png",
                    window, 0)},
            {HACHA, new Surface(
                    "../client/resources/images/hacha_t.png",
                    window, 0)},
            {MARTILLO, new Surface(
                    "../client/resources/images/martillo_t.png",
                    window, 0)},
            {VARA_FRESNO, new Surface(
                    "../client/resources/images/vara_fresno_t.png",
                    window, 0)},
            {FLAUTA_ELFICA, new Surface(
                    "../client/resources/images/flauta_elfica_t.png",
                    window, 0)},
            {BACULO_NUDOSO, new Surface(
                    "../client/resources/images/baculo_nudoso_t.png",
                    window, 0)},
            {BACULO_ENGARZADO, new Surface(
                    "../client/resources/images/baculo_engarzado_t.png",
                    window, 0)},
            {ARCO_SIMPLE, new Surface(
                    "../client/resources/images/arco_simple_t.png",
                    window, 0)},
            {ARCO_COMPUESTO, new Surface(
                    "../client/resources/images/arco_compuesto_t.png",
                    window, 0)},
            {ARMADURA_CUERO, new Surface(
                    "../client/resources/images/armadura_cuero_t.png",
                    window, 0)},
            {ARMADURA_PLACAS, new Surface(
                    "../client/resources/images/armadura_placas_t.png",
                    window, 0)},
            {TUNICA_AZUL, new Surface(
                    "../client/resources/images/tunica_azul_t.png",
                    window, 0)},
            {CAPUCHA, new Surface(
                    "../client/resources/images/capucha_t.png",
                    window, 0)},
            {CASCO_HIERRO, new Surface(
                    "../client/resources/images/casco_hierro_t.png",
                    window, 0)},
            {SOMBRERO_MAGICO, new Surface(
                    "../client/resources/images/sombrero_magico_t.png",
                    window, 0)},
            {ESCUDO_TORTUGA, new Surface(
                    "../client/resources/images/escudo_tortuga_t.png",
                    window, 0)},
            {ESCUDO_HIERRO, new Surface(
                    "../client/resources/images/escudo_hierro_t.png",
                    window, 0)},
            {POCION_VIDA, new Surface(
                    "../client/resources/images/pocion_vida_t.png",
                    window, 0)},
            {POCION_MANA, new Surface(
                    "../client/resources/images/pocion_mana_t.png",
                    window, 0)},
    };


    Surface* life_bar = new Surface("../client/resources/images/life_bar.png",
            window, 0);
    Surface* black_bar = new Surface(
            "../client/resources/images/black_bar.png", window, 0);
    Surface* mana_bar = new Surface(
            "../client/resources/images/mana_bar.png", window, 0);
    Surface* experience_bar = new Surface(
            "../client/resources/images/experience_bar.png", window, 0);

    infoSurfacesMap = {
            {LIFE, life_bar},
            {MANA, mana_bar},
            {EXPERIENCE, experience_bar},
            {BACKGROUND,black_bar}
    };
}

void GameRender::setTilesSize(int width,int height) {
    blocksWidth = width;
    blocksHeight = height;
    window.setTilesSize(width,height);
}

std::map<int, float> GameRender::getRenderablePlayerInfo() {
    std::map<int, float> playerInfo = {
            //TODO RECIBIR EXPERIENCE max
            {LIFE, ((float) current_world.main_player.actual_life)/
                            current_world.main_player.max_life},
            {MANA, ((float) current_world.player_info.actual_mana)/
                            current_world.player_info.max_mana},
            {EXPERIENCE, ((float) current_world.player_info.actual_experience)/
                            current_world.player_info.actual_experience}
    };
    std::cout << "\n\n\n esto es life " << playerInfo[LIFE];
    return std::move(playerInfo);
}

void GameRender::run() {
    using ms = std::chrono::milliseconds;
    std::this_thread::sleep_for(ms(500));
    blocksWidth = mapMonitor.getPlayerVisionWidth();
    blocksHeight = mapMonitor.getPlayerVisionHeight();
    window.setTilesSize(blocksWidth,blocksHeight);
    window.renderGameFrame(createGameFrameSurface());

    while (keepRunning) {
        current_world = mapMonitor.getCurrentWorld();
        renderTerrain(current_world.terrains);
        renderPlayers(current_world.players);
        renderNpcs(current_world.npcs);
        renderCreatures(current_world.creatures);
        //simulamos inventario recibido de server
        std::vector<Surface*> inventory_items =
                {new Surface("../client/resources/images/pocion_mana_t.png",
                 window, 0),
                 new Surface("../client/resources/images/armadura_cuero_t.png",
                         window, 0),
                 new Surface("../client/resources/images/pocion_mana_t.png",
                         window, 0),
                 new Surface("../client/resources/images/arco_compuesto_t.png",
                         window, 0),
                 new Surface("../client/resources/images/pocion_mana_t.png",
                         window, 0),
                 new Surface("../client/resources/images/escudo_tortuga_t.png",
                         window, 0),
                 new Surface("../client/resources/images/capucha_t.png",
                         window, 0)};
        window.renderInventory(inventory_items);
        //cuando lleguen los items del server los renderizamos
        //renderItems(floor_items);
        //simulamos un player, despues poner el posta sacado de current_world
        player_t player;
        player.shield = ESCUDO_HIERRO;
        player.armor = ARMADURA_CUERO;
        player.helmet = NO_ITEM_EQUIPPED;
        player.weapon = ARCO_COMPUESTO;
        window.renderEquipped(player, floorItemSurfacesMap);
        window.renderPlayerInfo(getRenderablePlayerInfo(),
                infoSurfacesMap);
        window.renderList(inventory_items);
        window.UpdateWindowSurface();
        std::this_thread::sleep_for(ms(10));
    }
}

int GameRender::getInventoryItemByPosition(int x, int y) {
    //size_t inventory_length = current_world.player_info.inventory.length;
    int position = window.getRenderedItemIndexByPosition(x, y, 7);
    if (position < 0) throw ItemException(
            "El inventario no tiene items en la posicion clickeada");
    /*if (current_world.player_info.inventory.length < position) throw
            ItemException("El inventario ya no tiene ese item");*/
    std::cout << "\n\nESTA ES LA POSITION DE INVENTARIO" << position;

//    return current_world.player_info.inventory.items[position];
    return 1;
}


int GameRender::getListItemByPosition(int x, int y) {
    //size_t inventory_length = current_world.player_info.list.length;
    int position = window.getRenderedListIndexByPosition(x, y, 7);
    if (position < 0) throw ItemException(
                "la lista no tiene items en la posicion clickeada");
    /*if (current_world.player_info.inventory.length < position) throw
                ItemException("la lista ya no tiene ese item");*/
    std::cout << "\n\nESTA ES LA POSITION DE list" << position;
    //return current_world.player_info.inventory.items[position];
    return 1;
}

int GameRender::isClickingListItems(int x, int y) {
    return window.isClickingListItems(x, y);
}

int GameRender::isClickingListGold(int x, int y) {
    return window.isClickingListGold(x, y);
}
int GameRender::isClickingInventoryItems(int x, int y) {
    return window.isClickingInventoryItems(x, y);
}

int GameRender::isClickingInventoryGold(int x, int y) {
    return window.isClickingInventoryGold(x, y);
}


void GameRender::stop() {
    keepRunning = false;
}

bool GameRender::isDead()  {
    return (! isRunning);
}
