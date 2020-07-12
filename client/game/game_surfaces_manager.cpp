
#include "game_Surfaces_manager.h"
#include "iostream"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"


GameSurfacesManager::GameSurfacesManager(SDLWindow& window) : window(window){}
GameSurfacesManager::~GameSurfacesManager(){
    for (auto const& surface : terrainSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : infoSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : itemSurfacesMap) {
        delete surface.second;
    }
    for (auto const& orientations : creatureSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : playerSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : npcSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    delete goldSurface;
    delete gameFrameSurface;
}

Surface* GameSurfacesManager::getTextSurface(std::string text) {
    return new Surface(text, window);
}


void GameSurfacesManager::createNecessaryTerrains(
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


void GameSurfacesManager::createNecessaryPlayers(
        std::vector<player_t>& players) {
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

void GameSurfacesManager::createNecessaryCreatures(
        std::vector<creature_t>& creatures) {
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


void GameSurfacesManager::createNecessaryNpcs(std::vector<npc_t>& npcs) {
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

void GameSurfacesManager::createNecessaryFrameItems(
        std::vector<uint8_t>& items) {
    for (auto& type: items) {
        if ((type != NO_ITEM_EQUIPPED) && (itemSurfacesMap.find(type)
            == itemSurfacesMap.end())) {
            Surface* surface = new Surface(
                    itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        }
    }
}


void GameSurfacesManager::createNecessaryItems(std::vector<item_t>& items) {
    for (auto& item: items) {
        int type = item.type;
        if (itemSurfacesMap.find(type)
            == itemSurfacesMap.end()) {
            Surface* surface = new Surface(
                    itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        }
    }
}
//todo refactor codigo repetido
void GameSurfacesManager::createNecessaryListItems(
        std::vector<list_item_t> items) {
    for (auto& item: items) {
        int type = item.type;
        if (itemSurfacesMap.find(type)
            == itemSurfacesMap.end()) {
            Surface* surface = new Surface(
                    itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        }
    }
}


void GameSurfacesManager::loadCreaturePaths() {
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
}

void GameSurfacesManager::loadNpcPaths() {
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
}


void GameSurfacesManager::loadPlayerPaths() {
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

void GameSurfacesManager::loadItemPaths() {
    itemSurfacesPaths = {
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
}

void GameSurfacesManager::loadSurfacePaths() {
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

    loadCreaturePaths();
    loadNpcPaths();
    loadPlayerPaths();
    loadItemPaths();
    createFrameSurfaces();
}
void GameSurfacesManager::createFrameSurfaces() {
    gameFrameSurface = new Surface(
            "../client/resources/images/game_frame.jpeg", window, 0);
    worldSurface = new Surface(
            "../client/resources/images/world.png", window, 0);
    goldSurface = new Surface(
            "../client/resources/images/gold_t.png", window, 1);
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
