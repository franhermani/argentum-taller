
#include "game_Surfaces_manager.h"
#include "iostream"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"
#include "../../common/defines/attacks.h"
#include "../../common/defines/states.h"
#include "../sdl/exception.h"


GameSurfacesManager::GameSurfacesManager(SDLWindow& window) : window(window) {
    mainFont = TTF_OpenFont("../client/resources/fonts/goudy.ttf", 100);
    if (mainFont == NULL) {
        throw SDLException("\nError al cargar font de surfaces",
                           SDL_GetError());
    }
    mainColor = {255, 255,255};
}
GameSurfacesManager::~GameSurfacesManager(){
    for (auto const& surface : infoSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : textSurfaces) {
        delete surface.second;
    }
    for (auto const& surface : itemSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : animatedStateMap) {
        delete surface.second;
    }
    for (auto const& orientations : creatureSurfacesMap) {
        for (auto const& surface : orientations.second)  delete surface.second;
    }
    for (auto const& orientations : stateSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : playerSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : npcSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }
    for (auto & orientations : attackSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
    }

    delete goldSurface;
    delete gameFrameSurface;
    delete worldSurface;
    TTF_CloseFont(mainFont);
}


Surface* GameSurfacesManager::operator()(std::string text) {
    if (textSurfaces.find(text)
        == textSurfaces.end()) {
        Surface* surface = new Surface(text, window, mainFont, mainColor);
        //guardamos para luego liberar memoria
        textSurfaces.insert({text, surface});
        return surface;
    }
    return textSurfaces[text];
}


Surface* GameSurfacesManager::operator()(stateType state, int orientation) {
    return stateSurfacesMap[state][orientation];
}


Surface* GameSurfacesManager::operator()(attack_t& attack) {
    int type = attack.type;
    int orientation = attack.orientation;
    if (attackSurfacesMap[type].find(orientation)
        == attackSurfacesMap[type].end()) {
        Surface* surface = new Surface(
                attackSurfacesPaths[type][orientation], window, 1);
        attackSurfacesMap[type].insert({orientation, surface});
        return surface;
    } else {
        return attackSurfacesMap[type][orientation];
    }
}


Surface* GameSurfacesManager::operator()(npc_t& npc) {
    int type = npc.type;
    int orientation = npc.orientation;
    if (npcSurfacesMap[type].find(orientation)
        == npcSurfacesMap[type].end()) {
        Surface* surface = new Surface(
                npcSurfacesPaths[type][orientation], window, 1);
        npcSurfacesMap[type].insert({orientation, surface});
        return surface;
    } else {
        return npcSurfacesMap[type][orientation];
    }
}

Surface* GameSurfacesManager::operator()(creature_t& creature) {
    int type = creature.type;
    int orientation = creature.orientation;
    if (creatureSurfacesMap[type].find(orientation)
        == creatureSurfacesMap[type].end()) {
        Surface *surface = new Surface(
                creatureSurfacesPaths[type][orientation], window, 1);
        creatureSurfacesMap[type].insert({orientation, surface});
        return surface;
    } else {
        return creatureSurfacesMap[type][orientation];
    }
}


Surface* GameSurfacesManager::operator()(player_t& player) {
    int race = player.race_type;
    int orientation = player.orientation;
    if (playerSurfacesMap[race].find(orientation)
        == playerSurfacesMap[race].end()) {
        Surface* surface = new Surface(
                playerSurfacesPaths[race][orientation], window, 1);
        playerSurfacesMap[race].insert({orientation, surface});
        return surface;
    } else {
        return playerSurfacesMap[race][orientation];
    }
}


Surface* GameSurfacesManager::operator()(int item_type) {
    if (itemSurfacesMap.find(item_type)
        == itemSurfacesMap.end()) {
        Surface* surface = new Surface(
                itemSurfacesPaths[item_type], window, 1);
        itemSurfacesMap.insert({item_type, surface});
        return surface;
    } else {
        return itemSurfacesMap[item_type];
    }
}


std::vector<Surface*> GameSurfacesManager::operator()(
        std::vector<list_item_t> items) {
    std::vector<Surface*> surfaces;
    for (auto& item: items) {
        int type = item.type;
        Surface* surface;
        if (itemSurfacesMap.find(type)
            == itemSurfacesMap.end()) {
            surface = new Surface(
                    itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        } else {
            surface = itemSurfacesMap[type];
        }
        surfaces.push_back(surface);
    }
    return surfaces;
}

Surface* GameSurfacesManager::animation(stateType state) {
    if (animatedStateMap.find(state)
        == animatedStateMap.end()) {
        if (animatedStatePaths.find(state)
            == animatedStatePaths.end()) {
            throw SurfaceExistanceException("Surface no existente");
        } else {
            Surface* surface = new Surface(
                    animatedStatePaths[state], window, 1);
            animatedStateMap.insert({state, surface});
            return surface;
        }
    }
    return animatedStateMap[state];
}

Surface* GameSurfacesManager::getEquipped(
        int weapon, int orientation) {
    if (equippedWeaponSurfacesMap[weapon].find(orientation)
            == equippedWeaponSurfacesMap[weapon].end()) {
            Surface* surface = new Surface(
                    equippedWeaponSurfacesPaths[weapon][orientation],
                    window, 1);
            equippedWeaponSurfacesMap[weapon].insert({orientation, surface});
            return surface;
    }
    return equippedWeaponSurfacesMap[weapon][orientation];
}

void GameSurfacesManager::createNecessaryFrameItems(
        std::vector<uint8_t>& items) {
    for (auto& type: items) {
        if (itemSurfacesPaths.find(type)
           == itemSurfacesPaths.end()) continue;
        if (itemSurfacesMap.find(type)
            == itemSurfacesMap.end()) {
            Surface* surface = new Surface(
                    itemSurfacesPaths[type], window, 1);
            itemSurfacesMap.insert({type, surface});
        }
    }
}


void GameSurfacesManager::loadAnimatedPaths() {
    animatedStatePaths = {
            {STATE_MEDITATING,
             "../client/resources/images/characters/meditating_anim_t.png"},
            {STATE_REVIVING,
             "../client/resources/images/characters/reviving_anim_t.png"},
    };
}

void GameSurfacesManager::loadCreaturePaths() {
    //CRIATURAS
    std::map<int, std::string> skeleton_orientations = {
            {UP, "../client/resources/images/characters/skeleton_up_t.png"},
            {DOWN, "../client/resources/images/characters/skeleton_down_t.png"},
            {LEFT, "../client/resources/images/characters/skeleton_left_t.png"},
            {RIGHT,
             "../client/resources/images/characters/skeleton_right_t.png"}
    };
    std::map<int, std::string> goblin_orientations = {
            {UP, "../client/resources/images/characters/goblin_up_t.png"},
            {DOWN, "../client/resources/images/characters/goblin_down_t.png"},
            {LEFT, "../client/resources/images/characters/goblin_left_t.png"},
            {RIGHT, "../client/resources/images/characters/goblin_right_t.png"}
    };

    std::map<int, std::string> zombie_orientations = {
            {UP, "../client/resources/images/characters/zombie_up_t.png"},
            {DOWN, "../client/resources/images/characters/zombie_down_t.png"},
            {LEFT, "../client/resources/images/characters/zombie_left_t.png"},
            {RIGHT, "../client/resources/images/characters/zombie_right_t.png"}
    };
    std::map<int, std::string> spider_orientations = {
            {UP, "../client/resources/images/characters/spider_up_t.png"},
            {DOWN, "../client/resources/images/characters/spider_down_t.png"},
            {LEFT, "../client/resources/images/characters/spider_left_t.png"},
            {RIGHT, "../client/resources/images/characters/spider_right_t.png"}
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

void GameSurfacesManager::loadEquippedPaths() {
    std::map<int, std::string> baculo_orientations = {
            {UP, "../client/resources/images/weapons/baculo_nudoso_up_p_t.png"},
            {DOWN,
             "../client/resources/images/weapons/baculo_nudoso_down_p_t.png"},
            {LEFT,
             "../client/resources/images/weapons/baculo_nudoso_right_p_t.png"},
            {RIGHT,
             "../client/resources/images/weapons/baculo_nudoso_left_p_t.png"}
    };
    std::map<int, std::string> arco_compuesto_orientations = {
            {UP,
             "../client/resources/images/weapons/arco_compuesto_up_p_t.png"},
            {DOWN,
             "../client/resources/images/weapons/arco_compuesto_down_p_t.png"},
            {LEFT,
             "../client/resources/images/weapons/arco_compuesto_right_p_t.png"},
            {RIGHT,
             "../client/resources/images/weapons/arco_compuesto_left_p_t.png"}
    };
    std::map<int, std::string> arco_simple_orientations = {
            {UP, "../client/resources/images/weapons/arco_simple_up_p_t.png"},
            {DOWN,
             "../client/resources/images/weapons/arco_simple_down_p_t.png"},
            {LEFT,
             "../client/resources/images/weapons/arco_simple_left_p_t.png"},
            {RIGHT,
             "../client/resources/images/weapons/arco_simple_right_p_t.png"}
    };
    std::map<int, std::string> baculo_engarzado_orientations = {
            {UP,
             "../client/resources/images/weapons/baculo_engarzado_up_p_t.png"},
            {DOWN,
          "../client/resources/images/weapons/baculo_engarzado_down_p_t.png"},
            {LEFT,
          "../client/resources/images/weapons/baculo_engarzado_right_p_t.png"},
            {RIGHT,
             "../client/resources/images/weapons/baculo_engarzado_left_p_t.png"}
    };
    std::map<int, std::string> espada_orientations = {
            {UP, "../client/resources/images/weapons/espada_up_p_t.png"},
            {DOWN, "../client/resources/images/weapons/espada_down_p_t.png"},
            {LEFT, "../client/resources/images/weapons/espada_right_p_t.png"},
            {RIGHT, "../client/resources/images/weapons/espada_left_p_t.png"}
    };
    std::map<int, std::string> flauta_elfica_orientations = {
            {UP, "../client/resources/images/weapons/flauta_elfica_up_p_t.png"},
            {DOWN,
             "../client/resources/images/weapons/flauta_elfica_down_p_t.png"},
            {LEFT,
             "../client/resources/images/weapons/flauta_elfica_right_p_t.png"},
            {RIGHT,
             "../client/resources/images/weapons/flauta_elfica_left_p_t.png"}
    };
    std::map<int, std::string> hacha_orientations = {
            {UP, "../client/resources/images/weapons/hacha_up_p_t.png"},
            {DOWN, "../client/resources/images/weapons/hacha_down_p_t.png"},
            {LEFT, "../client/resources/images/weapons/hacha_right_p_t.png"},
            {RIGHT, "../client/resources/images/weapons/hacha_left_p_t.png"}
    };
    std::map<int, std::string> martillo_orientations = {
            {UP, "../client/resources/images/weapons/martillo_up_p_t.png"},
            {DOWN,
             "../client/resources/images/weapons/martillo_down_p_t.png"},
            {LEFT,
             "../client/resources/images/weapons/martillo_right_p_t.png"},
            {RIGHT,
             "../client/resources/images/weapons/martillo_left_p_t.png"}
    };

    std::map<int, std::string> armadura_placas_orientations = {
            {UP, "../client/resources/images/items/armadura_placas_up_p_t.png"},
            {DOWN,
             "../client/resources/images/items/armadura_placas_down_p_t.png"},
            {LEFT,
             "../client/resources/images/items/armadura_placas_left_p_t.png"},
            {RIGHT,
             "../client/resources/images/items/armadura_placas_right_p_t.png"}
    };
    std::map<int, std::string> armadura_cuero_orientations = {
            {UP, "../client/resources/images/items/armadura_cuero_up_t.png"},
            {DOWN,
             "../client/resources/images/items/armadura_cuero_down_t.png"},
            {LEFT,
             "../client/resources/images/items/armadura_cuero_left_t.png"},
            {RIGHT,
             "../client/resources/images/items/armadura_cuero_right_t.png"}
    };
    std::map<int, std::string> tunica_azul_orientations = {
            {UP, "../client/resources/images/items/tunica_azul_up_t.png"},
            {DOWN, "../client/resources/images/items/tunica_azul_down_t.png"},
            {LEFT, "../client/resources/images/items/tunica_azul_left_t.png"},
            {RIGHT, "../client/resources/images/items/tunica_azul_right_t.png"}
    };
    std::map<int, std::string> escudo_hierro_orientations = {
            {UP, "../client/resources/images/items/escudo_hierro_up_p_t.png"},
            {DOWN,
             "../client/resources/images/items/escudo_hierro_down_p_t.png"},
            {LEFT,
             "../client/resources/images/items/escudo_hierro_right_p_t.png"},
            {RIGHT,
             "../client/resources/images/items/escudo_hierro_left_p_t.png"}
    };
    std::map<int, std::string> escudo_tortuga_orientations = {
            {UP, "../client/resources/images/items/escudo_tortuga_up_t.png"},
            {DOWN,
             "../client/resources/images/items/escudo_tortuga_down_t.png"},
            {LEFT,
             "../client/resources/images/items/escudo_tortuga_right_t.png"},
            {RIGHT,
             "../client/resources/images/items/escudo_tortuga_left_t.png"}
    };
    std::map<int, std::string> capucha_orientations = {
            {UP, "../client/resources/images/items/capucha_up_t.png"},
            {DOWN, "../client/resources/images/items/capucha_down_t.png"},
            {LEFT, "../client/resources/images/items/capucha_left_t.png"},
            {RIGHT, "../client/resources/images/items/capucha_right_t.png"}
    };
    std::map<int, std::string> casco_hierro_orientations = {
            {UP, "../client/resources/images/items/casco_hierro_up_t.png"},
            {DOWN, "../client/resources/images/items/casco_hierro_down_t.png"},
            {LEFT, "../client/resources/images/items/casco_hierro_right_t.png"},
            {RIGHT, "../client/resources/images/items/casco_hierro_left_t.png"}
    };

    std::map<int, std::string> sombrero_magico_orientations = {
            {UP, "../client/resources/images/items/sombrero_magico_up_t.png"},
            {DOWN,
             "../client/resources/images/items/sombrero_magico_down_t.png"},
            {LEFT,
             "../client/resources/images/items/sombrero_magico_right_t.png"},
            {RIGHT,
             "../client/resources/images/items/sombrero_magico_left_t.png"}
    };



    equippedWeaponSurfacesPaths = {
            {ESPADA, espada_orientations},
            {HACHA, hacha_orientations},
            {MARTILLO, martillo_orientations},
            {VARA_FRESNO, baculo_orientations},
            {FLAUTA_ELFICA, flauta_elfica_orientations},
            {BACULO_NUDOSO, baculo_orientations},
            {BACULO_ENGARZADO,
                    baculo_engarzado_orientations},
            {ARCO_SIMPLE, arco_simple_orientations},
            {ARCO_COMPUESTO,
                    arco_compuesto_orientations},
            {ESCUDO_HIERRO, escudo_hierro_orientations},
            {ESCUDO_TORTUGA, escudo_tortuga_orientations},
            {ARMADURA_CUERO, armadura_cuero_orientations},
            {ARMADURA_PLACAS, armadura_placas_orientations},
            {TUNICA_AZUL, tunica_azul_orientations},
            {CASCO_HIERRO, casco_hierro_orientations},
            {CAPUCHA, capucha_orientations},
            {SOMBRERO_MAGICO, sombrero_magico_orientations}
    };

    std::map<int, Surface*> baculo_nudoso_surfaces;
    std::map<int, Surface*> arco_compuesto_surfaces;
    std::map<int, Surface*> arco_simple_surfaces;
    std::map<int, Surface*> baculo_engarzado_surfaces;
    std::map<int, Surface*> flauta_elfica_surfaces;
    std::map<int, Surface*> vara_fresno_surfaces;
    std::map<int, Surface*> martilo_surfaces;
    std::map<int, Surface*> hacha_surfaces;
    std::map<int, Surface*> espada_surfaces;
    std::map<int, Surface*> armadura_placas_surfaces;
    std::map<int, Surface*> armadura_cuero_surfaces;
    std::map<int, Surface*> tunica_azul_surfaces;
    std::map<int, Surface*> escudo_hierro_surfaces;
    std::map<int, Surface*> escudo_tortuga_surfaces;
    std::map<int, Surface*> capucha_surfaces;
    std::map<int, Surface*> casco_hierro_surfaces;
    std::map<int, Surface*> sombrero_magico_surfaces;
    equippedWeaponSurfacesMap = {
            {ESPADA, espada_surfaces},
            {HACHA, hacha_surfaces},
            {MARTILLO, martilo_surfaces},
            {VARA_FRESNO, vara_fresno_surfaces},
            {FLAUTA_ELFICA, flauta_elfica_surfaces},
            {BACULO_NUDOSO, baculo_nudoso_surfaces},
            {BACULO_ENGARZADO,
                    baculo_engarzado_surfaces},
            {ARCO_SIMPLE, arco_simple_surfaces},
            {ARCO_COMPUESTO,
                    arco_compuesto_surfaces},
            {ARMADURA_PLACAS, armadura_placas_surfaces},
            {ARMADURA_CUERO, armadura_cuero_surfaces},
            {ESCUDO_TORTUGA, escudo_tortuga_surfaces},
            {ESCUDO_HIERRO, escudo_hierro_surfaces},
            {TUNICA_AZUL, tunica_azul_surfaces},
            {CASCO_HIERRO, casco_hierro_surfaces},
            {CAPUCHA, capucha_surfaces},
            {SOMBRERO_MAGICO, sombrero_magico_surfaces}
    };
}


void GameSurfacesManager::loadNpcPaths() {
    //npcs
    std::map<int, std::string> banker_orientations = {
            {UP, "../client/resources/images/characters/banker_up_t.png"},
            {DOWN, "../client/resources/images/characters/banker_down_t.png"},
            {LEFT, "../client/resources/images/characters/banker_left_t.png"},
            {RIGHT, "../client/resources/images/characters/banker_right_t.png"}
    };
    std::map<int, std::string> priest_orientations = {
            {UP, "../client/resources/images/characters/priest_up_t.png"},
            {DOWN, "../client/resources/images/characters/priest_down_t.png"},
            {LEFT, "../client/resources/images/characters/priest_left_t.png"},
            {RIGHT, "../client/resources/images/characters/priest_right_t.png"}
    };
    std::map<int, std::string> merchant_orientations = {
            {UP, "../client/resources/images/characters/merchant_up_t.png"},
            {DOWN, "../client/resources/images/characters/merchant_down_t.png"},
            {LEFT, "../client/resources/images/characters/merchant_left_t.png"},
            {RIGHT,
             "../client/resources/images/characters/merchant_right_t.png"}
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



void GameSurfacesManager::loadAttackPaths() {
    std::map<int, std::string> multiple_arrow_orientations = {
            {UP, "../client/resources/images/attacks/triple_arrow_up_t.png"},
            {DOWN,
             "../client/resources/images/attacks/triple_arrow_down_t.png"},
            {LEFT,
             "../client/resources/images/attacks/triple_arrow_left_t.png"},
            {RIGHT,
             "../client/resources/images/attacks/triple_arrow_right_t.png"}
    };
    std::map<int, std::string> magic_arrow_orientations = {
            {UP, "../client/resources/images/attacks/magic_arrow_up_t.png"},
            {DOWN, "../client/resources/images/attacks/magic_arrow_down_t.png"},
            {LEFT, "../client/resources/images/attacks/magic_arrow_left_t.png"},
            {RIGHT,
             "../client/resources/images/attacks/magic_arrow_right_t.png"}
    };
    std::map<int, std::string> single_arrow_orientations = {
            {UP, "../client/resources/images/attacks/single_arrow_up_t.png"},
            {DOWN,
             "../client/resources/images/attacks/single_arrow_down_t.png"},
            {LEFT,
             "../client/resources/images/attacks/single_arrow_left_t.png"},
            {RIGHT,
             "../client/resources/images/attacks/single_arrow_right_t.png"}
    };
    std::map<int, std::string> melee_orientations = {
            {UP, "../client/resources/images/attacks/melee_attack_t_big.png"},
            {DOWN, "../client/resources/images/attacks/melee_attack_t_big.png"},
            {LEFT, "../client/resources/images/attacks/melee_attack_t_big.png"},
            {RIGHT, "../client/resources/images/attacks/melee_attack_t_big.png"}
    };
    std::map<int, std::string> no_weapon_melee_orientations = {
            {UP,
             "../client/resources/images/attacks/hit_effect_2_small_t.png"},
            {DOWN,
             "../client/resources/images/attacks/hit_effect_2_small_t.png"},
            {LEFT,
             "../client/resources/images/attacks/hit_effect_2_small_t.png"},
            {RIGHT,
             "../client/resources/images/attacks/hit_effect_2_small_t.png"}
    };
    std::map<int, std::string> missile_orientations = {
            {UP, "../client/resources/images/attacks/missile_up_t.png"},
            {DOWN, "../client/resources/images/attacks/missile_down_t.png"},
            {LEFT, "../client/resources/images/attacks/missile_left_t.png"},
            {RIGHT, "../client/resources/images/attacks/missile_right_t.png"}
    };

    std::map<int, std::string> explosion_spell_orientations = {
            {UP, "../client/resources/images/attacks/explosion_t.png"},
            {DOWN, "../client/resources/images/attacks/explosion_t.png"},
            {LEFT, "../client/resources/images/attacks/explosion_t.png"},
            {RIGHT, "../client/resources/images/attacks/explosion_t.png"}
    };

    std::map<int, std::string> heal_spell_orientations = {
            {UP, "../client/resources/images/attacks/heal_t.png"},
            {DOWN, "../client/resources/images/attacks/heal_t.png"},
            {LEFT, "../client/resources/images/attacks/heal_t.png"},
            {RIGHT, "../client/resources/images/attacks/heal_t.png"}
    };

    attackSurfacesPaths = {
            {MULTIPLE_ARROW, multiple_arrow_orientations},
            {SINGLE_ARROW, single_arrow_orientations},
            {MELEE, melee_orientations},
            {NO_WEAPON_MELEE, no_weapon_melee_orientations},
            {MAGIC_ARROW_SPELL, magic_arrow_orientations},
            {HEAL_SPELL, heal_spell_orientations},
            {MISSILE_SPELL, missile_orientations},
            {EXPLOSION_SPELL, explosion_spell_orientations}
    };
    std::map<int, Surface*> multiple_arrow_surfaces;
    std::map<int, Surface*> single_arrow_surfaces;
    std::map<int, Surface*> missile_surfaces;
    std::map<int, Surface*> magic_arrow_surfaces;
    std::map<int, Surface*> explosion_spell_surfaces;
    std::map<int, Surface*> heal_spell_surfaces;
    std::map<int, Surface*> melee_surfaces;
    std::map<int, Surface*> no_weapon_melee_surfaces;
    attackSurfacesMap = {{MULTIPLE_ARROW, multiple_arrow_surfaces},
                         {SINGLE_ARROW,   single_arrow_surfaces},
                         {MELEE, melee_surfaces},
                         {MAGIC_ARROW_SPELL, magic_arrow_surfaces},
                         {HEAL_SPELL, heal_spell_surfaces},
                         {MISSILE_SPELL, missile_surfaces},
                         {EXPLOSION_SPELL, explosion_spell_surfaces},
                         {NO_WEAPON_MELEE, no_weapon_melee_surfaces}
    };
}

void GameSurfacesManager::loadPlayerPaths() {
    //JUGADORES

    std::map<int, std::string> human_orientations = {
            {UP, "../client/resources/images/characters/human_up_t.png"},
            {DOWN, "../client/resources/images/characters/human_down_t.png"},
            {LEFT, "../client/resources/images/characters/human_left_t.png"},
            {RIGHT, "../client/resources/images/characters/human_right_t.png"}
    };
    std::map<int, std::string> elf_orientations = {
            {UP, "../client/resources/images/characters/elf_up_t.png"},
            {DOWN, "../client/resources/images/characters/elf_down_t.png"},
            {LEFT, "../client/resources/images/characters/elf_left_t.png"},
            {RIGHT, "../client/resources/images/characters/elf_right_t.png"}
    };
    std::map<int, std::string> dwarf_orientations = {
            {UP, "../client/resources/images/characters/dwarf_up_t.png"},
            {DOWN, "../client/resources/images/characters/dwarf_down_t.png"},
            {LEFT, "../client/resources/images/characters/dwarf_left_t.png"},
            {RIGHT, "../client/resources/images/characters/dwarf_right_t.png"}
    };
    std::map<int, std::string> gnome_orientations = {
            {UP, "../client/resources/images/characters/gnome_up_t.png"},
            {DOWN, "../client/resources/images/characters/gnome_down_t.png"},
            {LEFT, "../client/resources/images/characters/gnome_left_t.png"},
            {RIGHT, "../client/resources/images/characters/gnome_right_t.png"}
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
    std::map<int, Surface*> ghostSurfacesMap = {
            {UP,    new Surface(
                    "../client/resources/images/characters/ghost_up_t.png",
                    window, 1)},
            {DOWN,  new Surface(
                    "../client/resources/images/characters/ghost_down_t.png",
                    window, 1)},
            {LEFT,  new Surface(
                    "../client/resources/images/characters/ghost_left_t.png",
                    window, 1)},
            {RIGHT, new Surface(
                    "../client/resources/images/characters/ghost_right_t.png",
                    window, 1)}
    };
    std::map<int, Surface*> reviveSurfacesMap = {
            {UP,    new Surface(
                    "../client/resources/images/characters/reviving_up_t.png",
                    window, 1)},
            {DOWN,  new Surface(
                    "../client/resources/images/characters/reviving_down_t.png",
                    window, 1)},
            {LEFT,  new Surface(
                    "../client/resources/images/characters/reviving_left_t.png",
                    window, 1)},
            {RIGHT, new Surface(
             "../client/resources/images/characters/reviving_right_t.png",
                    window, 1)}
    };
    std::map<int, Surface*> meditateSurfacesMap = {
            {UP,    new Surface(
                    "../client/resources/images/characters/meditating_up_t.png",
                    window, 1)},
            {DOWN,  new Surface(
             "../client/resources/images/characters/meditating_down_t.png",
                    window, 1)},
            {LEFT,  new Surface(
             "../client/resources/images/characters/meditating_left_t.png",
                    window, 1)},
            {RIGHT, new Surface(
            "../client/resources/images/characters/meditating_right_t.png",
                    window, 1)}
    };
    std::map<int, Surface*> dyingSurfacesMap = {
            {UP,    new Surface(
             "../client/resources/images/characters/dying_creature_up_t.png",
                    window, 1)},
            {DOWN,  new Surface(
             "../client/resources/images/characters/dying_creature_down_t.png",
                    window, 1)},
            {LEFT,  new Surface(
            "../client/resources/images/characters/dying_creature_left_t.png",
                    window, 1)},
            {RIGHT, new Surface(
             "../client/resources/images/characters/dying_creature_right_t.png",
                    window, 1)}
    };
    stateSurfacesMap = {
            {STATE_GHOST, ghostSurfacesMap},
            {STATE_REVIVING, reviveSurfacesMap},
            {STATE_MEDITATING, meditateSurfacesMap},
            {STATE_DYING, dyingSurfacesMap}
    };
}

void GameSurfacesManager::loadItemPaths() {
    itemSurfacesPaths = {
            {ESPADA, "../client/resources/images/weapons/espada_t.png"},
            {HACHA, "../client/resources/images/weapons/hacha_t.png"},
            {MARTILLO, "../client/resources/images/weapons/martillo_t.png"},
            {VARA_FRESNO,
             "../client/resources/images/weapons/vara_fresno_t.png"},
            {FLAUTA_ELFICA,
                 "../client/resources/images/weapons/flauta_elfica_t.png"},
            {BACULO_NUDOSO,
                "../client/resources/images/weapons/baculo_nudoso_t.png"},
            {BACULO_ENGARZADO,
             "../client/resources/images/weapons/baculo_engarzado_t.png"},
            {ARCO_SIMPLE,
             "../client/resources/images/weapons/arco_simple_t.png"},
            {ARCO_COMPUESTO,
                    "../client/resources/images/weapons/arco_compuesto_t.png"},
            {ARMADURA_CUERO,
                    "../client/resources/images/items/armadura_cuero_t.png"},
            {ARMADURA_PLACAS,
                    "../client/resources/images/items/armadura_placas_t.png"},
            {TUNICA_AZUL,
                    "../client/resources/images/items/tunica_azul_t.png"},
            {CAPUCHA, "../client/resources/images/items/capucha_t.png"},
            {CASCO_HIERRO,
                "../client/resources/images/items/casco_hierro_t.png"},
            {SOMBRERO_MAGICO,
                    "../client/resources/images/items/sombrero_magico_t.png"},
            {ESCUDO_TORTUGA,
                    "../client/resources/images/items/escudo_tortuga_t.png"},
            {ESCUDO_HIERRO,
                "../client/resources/images/items/escudo_hierro_t.png"},
            {POCION_VIDA, "../client/resources/images/items/pocion_vida_t.png"},
            {POCION_MANA, "../client/resources/images/items/pocion_mana_t.png"},
    };
}

void GameSurfacesManager::loadSurfacePaths() {
    loadCreaturePaths();
    loadNpcPaths();
    loadPlayerPaths();
    loadItemPaths();
    loadAttackPaths();
    loadEquippedPaths();
    loadAnimatedPaths();
    createFrameSurfaces();
}
void GameSurfacesManager::createFrameSurfaces() {
    gameFrameSurface = new Surface(
            "../client/resources/images/etc/game_frame.jpeg", window, 0);
    worldSurface = new Surface(
            "../tiled/world.png", window, 0);
    goldSurface = new Surface(
            "../client/resources/images/items/gold_t.png", window, 1);
    Surface* life_bar = new Surface(
            "../client/resources/images/etc/life_bar.png",
            window, 0);
    Surface* black_bar = new Surface(
            "../client/resources/images/etc/black_bar.png", window, 0);
    Surface* mana_bar = new Surface(
            "../client/resources/images/etc/mana_bar.png", window, 0);
    Surface* experience_bar = new Surface(
            "../client/resources/images/etc/experience_bar.png", window, 0);

    infoSurfacesMap = {
            {LIFE, life_bar},
            {MANA, mana_bar},
            {EXPERIENCE, experience_bar},
            {BACKGROUND,black_bar}
    };
}
