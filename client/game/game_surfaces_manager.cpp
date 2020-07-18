
#include "game_Surfaces_manager.h"
#include "iostream"
#include "../../common/defines/world_structs.h"
#include "../../common/defines/races.h"
#include "../../common/defines/creatures.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/items.h"
#include "../../common/defines/attacks.h"
#include "../../common/defines/states.h"



GameSurfacesManager::GameSurfacesManager(SDLWindow& window) : window(window){}
GameSurfacesManager::~GameSurfacesManager(){
    //TODO CHEQUEO DE MATAR TODO

    for (auto const& surface : infoSurfacesMap) {
        delete surface.second;
    }
    for (auto const& surface : itemSurfacesMap) {
        delete surface.second;
    }
    for (auto const& orientations : creatureSurfacesMap) {
        for (auto const& surface : orientations.second) delete surface.second;
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
}

Surface* GameSurfacesManager::getTextSurface(std::string text) {
    return new Surface(text, window);
}


void GameSurfacesManager::createNecessaryEquipped(
        std::vector<player_t>& players) {
    //TODO hacer una funcion qeu te diga si una claave esta en el diccionario para no repetir

    //REFACTOR ACA URGENTE EHHH que es eso de chequear no item equipped en esto
    // Y AL MISmo tiempo chequearlo en gamerender
    for (auto& player: players) {
        int orientation = player.orientation;
        int weapon = player.weapon;
        if (weapon != NO_ITEM_EQUIPPED && (equippedWeaponSurfacesMap[weapon].find(orientation)
            == equippedWeaponSurfacesMap[weapon].end())) {
            if (equippedWeaponSurfacesPaths[weapon].find(orientation)
                == equippedWeaponSurfacesPaths[weapon].end()) {
                continue;
            }
            Surface* surface = new Surface(
                    equippedWeaponSurfacesPaths[weapon][orientation], window, 1);
            equippedWeaponSurfacesMap[weapon].insert({orientation, surface});
        }
        int armor = player.armor;
        if (armor != NO_ITEM_EQUIPPED && (equippedWeaponSurfacesMap[armor].find(orientation)
                                          == equippedWeaponSurfacesMap[armor].end())) {
            if (equippedWeaponSurfacesPaths[armor].find(orientation)
                == equippedWeaponSurfacesPaths[armor].end()) {
                continue;
            }
            Surface* surface = new Surface(
                    equippedWeaponSurfacesPaths[armor][orientation], window, 1);
            equippedWeaponSurfacesMap[armor].insert({orientation, surface});
        }
        int shield = player.shield;
        if (shield != NO_ITEM_EQUIPPED && (equippedWeaponSurfacesMap[shield].find(orientation)
            == equippedWeaponSurfacesMap[shield].end())) {
            if (equippedWeaponSurfacesPaths[shield].find(orientation)
                == equippedWeaponSurfacesPaths[shield].end()) {
                continue;
            }
            Surface* surface = new Surface(
                    equippedWeaponSurfacesPaths[shield][orientation], window, 1);
            equippedWeaponSurfacesMap[shield].insert({orientation, surface});
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

void GameSurfacesManager::loadEquippedPaths() {
    std::map<int, std::string> baculo_orientations = {
            {UP, "../client/resources/images/baculo_nudoso_up_p_t.png"},
            {DOWN, "../client/resources/images/baculo_nudoso_down_p_t.png"},
            {LEFT, "../client/resources/images/baculo_nudoso_right_p_t.png"},
            {RIGHT, "../client/resources/images/baculo_nudoso_left_p_t.png"}
    };
    std::map<int, std::string> arco_compuesto_orientations = {
            {UP, "../client/resources/images/arco_compuesto_up_p_t.png"},
            {DOWN, "../client/resources/images/arco_compuesto_down_p_t.png"},
            {LEFT, "../client/resources/images/arco_compuesto_right_p_t.png"},
            {RIGHT, "../client/resources/images/arco_compuesto_left_p_t.png"}
    };
    std::map<int, std::string> arco_simple_orientations = {
            {UP, "../client/resources/images/arco_simple_up_p_t.png"},
            {DOWN, "../client/resources/images/arco_simple_down_p_t.png"},
            {LEFT, "../client/resources/images/arco_simple_left_p_t.png"},
            {RIGHT, "../client/resources/images/arco_simple_right_p_t.png"}
    };
    std::map<int, std::string> baculo_engarzado_orientations = {
            {UP, "../client/resources/images/baculo_engarzado_up_p_t.png"},
            {DOWN, "../client/resources/images/baculo_engarzado_down_p_t.png"},
            {LEFT, "../client/resources/images/baculo_engarzado_right_p_t.png"},
            {RIGHT, "../client/resources/images/baculo_engarzado_left_p_t.png"}
    };
    std::map<int, std::string> espada_orientations = {
            {UP, "../client/resources/images/espada_up_p_t.png"},
            {DOWN, "../client/resources/images/espada_down_p_t.png"},
            {LEFT, "../client/resources/images/espada_right_p_t.png"},
            {RIGHT, "../client/resources/images/espada_left_p_t.png"}
    };
    std::map<int, std::string> flauta_elfica_orientations = {
            {UP, "../client/resources/images/flauta_elfica_up_p_t.png"},
            {DOWN, "../client/resources/images/flauta_elfica_down_p_t.png"},
            {LEFT, "../client/resources/images/flauta_elfica_right_p_t.png"},
            {RIGHT, "../client/resources/images/flauta_elfica_left_p_t.png"}
    };
    std::map<int, std::string> hacha_orientations = {
            {UP, "../client/resources/images/hacha_up_p_t.png"},
            {DOWN, "../client/resources/images/hacha_down_p_t.png"},
            {LEFT, "../client/resources/images/hacha_right_p_t.png"},
            {RIGHT, "../client/resources/images/hacha_left_p_t.png"}
    };
    std::map<int, std::string> martillo_orientations = {
            {UP, "../client/resources/images/martillo_up_p_t.png"},
            {DOWN, "../client/resources/images/martillo_down_p_t.png"},
            {LEFT, "../client/resources/images/martillo_right_p_t.png"},
            {RIGHT, "../client/resources/images/martillo_left_p_t.png"}
    };

    std::map<int, std::string> armadura_placas_orientations = {
            {UP, "../client/resources/images/armadura_placas_up_p_t.png"},
            {DOWN, "../client/resources/images/armadura_placas_down_p_t.png"},
            {LEFT, "../client/resources/images/armadura_placas_left_p_t.png"},
            {RIGHT, "../client/resources/images/armadura_placas_right_p_t.png"}
    };
    std::map<int, std::string> escudo_hierro_orientations = {
            {UP, "../client/resources/images/escudo_hierro_up_p_t.png"},
            {DOWN, "../client/resources/images/escudo_hierro_down_p_t.png"},
            {LEFT, "../client/resources/images/escudo_hierro_right_p_t.png"},
            {RIGHT, "../client/resources/images/escudo_hierro_left_p_t.png"}
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
            {ESCUDO_TORTUGA, escudo_hierro_orientations},
            {ARMADURA_CUERO, armadura_placas_orientations},
            {ARMADURA_PLACAS, armadura_placas_orientations},
            {TUNICA_AZUL, armadura_placas_orientations}
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
    std::map<int, Surface*> escudo_hierro_surfaces;
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
            {ARMADURA_CUERO, armadura_placas_surfaces},
            {ESCUDO_TORTUGA, escudo_hierro_surfaces},
            {ESCUDO_HIERRO, escudo_hierro_surfaces},
            {TUNICA_AZUL, armadura_placas_surfaces}
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




Surface* GameSurfacesManager::operator()(int state, int orientation) {
    //todo si hacer el create if necessary
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
    }
    else return attackSurfacesMap[type][orientation];
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
    }
    else return npcSurfacesMap[type][orientation];
}

Surface* GameSurfacesManager::operator()(creature_t& creature) {
    int type = creature.type;
    int orientation = creature.orientation;
    if (creatureSurfacesMap[type].find(orientation)
        == creatureSurfacesMap[type].end()) {
        Surface* surface = new Surface(
                creatureSurfacesPaths[type][orientation], window, 1);
        creatureSurfacesMap[type].insert({orientation, surface});
        return surface;
    }
    else return creatureSurfacesMap[type][orientation];
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
    }
    else return playerSurfacesMap[race][orientation];
}


Surface* GameSurfacesManager::operator()(int item_type) {
    if (itemSurfacesMap.find(item_type)
        == itemSurfacesMap.end()) {
        Surface* surface = new Surface(
                itemSurfacesPaths[item_type], window, 1);
        itemSurfacesMap.insert({item_type, surface});
        return surface;
    } else return itemSurfacesMap[item_type];
}


void GameSurfacesManager::loadAttackPaths() {
    std::map<int, std::string> multiple_arrow_orientations = {
            {UP, "../client/resources/images/triple_arrow_up_t.png"},
            {DOWN, "../client/resources/images/triple_arrow_down_t.png"},
            {LEFT, "../client/resources/images/triple_arrow_left_t.png"},
            {RIGHT, "../client/resources/images/triple_arrow_right_t.png"}
    };
    std::map<int, std::string> magic_arrow_orientations = {
            {UP, "../client/resources/images/magic_arrow_up_t.png"},
            {DOWN, "../client/resources/images/magic_arrow_down_t.png"},
            {LEFT, "../client/resources/images/magic_arrow_left_t.png"},
            {RIGHT, "../client/resources/images/magic_arrow_right_t.png"}
    };
    std::map<int, std::string> single_arrow_orientations = {
            {UP, "../client/resources/images/single_arrow_up_t.png"},
            {DOWN, "../client/resources/images/single_arrow_down_t.png"},
            {LEFT, "../client/resources/images/single_arrow_left_t.png"},
            {RIGHT, "../client/resources/images/single_arrow_right_t.png"}
    };
    std::map<int, std::string> melee_orientations = {
            {UP, "../client/resources/images/melee_attack_t_big.png"},
            {DOWN, "../client/resources/images/melee_attack_t_big.png"},
            {LEFT, "../client/resources/images/melee_attack_t_big.png"},
            {RIGHT, "../client/resources/images/melee_attack_t_big.png"}
    };
    std::map<int, std::string> missile_orientations = {
            {UP, "../client/resources/images/missile_up_t.png"},
            {DOWN, "../client/resources/images/missile_down_t.png"},
            {LEFT, "../client/resources/images/missile_left_t.png"},
            {RIGHT, "../client/resources/images/missile_right_t.png"}
    };

    std::map<int, std::string> explosion_spell_orientations = {
            {UP, "../client/resources/images/explosion_t.png"},
            {DOWN, "../client/resources/images/explosion_t.png"},
            {LEFT, "../client/resources/images/explosion_t.png"},
            {RIGHT, "../client/resources/images/explosion_t.png"}
    };

    std::map<int, std::string> heal_spell_orientations = {
            {UP, "../client/resources/images/heal_t.png"},
            {DOWN, "../client/resources/images/heal_t.png"},
            {LEFT, "../client/resources/images/heal_t.png"},
            {RIGHT, "../client/resources/images/heal_t.png"}
    };

    attackSurfacesPaths = {
            {MULTIPLE_ARROW, multiple_arrow_orientations},
            {SINGLE_ARROW, single_arrow_orientations},
            {MELEE, melee_orientations},
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
    attackSurfacesMap = {{MULTIPLE_ARROW, multiple_arrow_surfaces},
                         {SINGLE_ARROW,   single_arrow_surfaces},
                         {MELEE, melee_surfaces},
                         {MAGIC_ARROW_SPELL, magic_arrow_surfaces},
                         {HEAL_SPELL, heal_spell_surfaces},
                         {MISSILE_SPELL, missile_surfaces},
                         {EXPLOSION_SPELL, explosion_spell_surfaces}
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
    std::map<int, Surface*> ghostSurfacesMap = {{UP,    new Surface("../client/resources/images/ghost_up_t.png", window, 1)},
                        {DOWN,  new Surface("../client/resources/images/ghost_down_t.png", window, 1)},
                        {LEFT,  new Surface("../client/resources/images/ghost_left_t.png", window, 1)},
                        {RIGHT, new Surface("../client/resources/images/ghost_right_t.png", window, 1)}

    };
    // todo fixear esto
    std::map<int, Surface*> reviveSurfacesMap = {{UP,    new Surface("../client/resources/images/reviving_t.png", window, 1)},
                                                {DOWN,  new Surface("../client/resources/images/reviving_t.png", window, 1)},
                                                {LEFT,  new Surface("../client/resources/images/reviving_t.png", window, 1)},
                                                {RIGHT, new Surface("../client/resources/images/reviving_t.png", window, 1)}

    };
    //TODO FIXEAR MISMA RUTA

    std::map<int, Surface*> meditateSurfacesMap = {{UP,    new Surface("../client/resources/images/meditating_t.png", window, 1)},
                                                 {DOWN,  new Surface("../client/resources/images/meditating_t.png", window, 1)},
                                                 {LEFT,  new Surface("../client/resources/images/meditating_t.png", window, 1)},
                                                 {RIGHT, new Surface("../client/resources/images/meditating_t.png", window, 1)}

    };
    std::map<int, Surface*> dyingSurfacesMap = {{UP,    new Surface("../client/resources/images/dying_creature_t.png", window, 1)},
                                                   {DOWN,  new Surface("../client/resources/images/dying_creature_t.png", window, 1)},
                                                   {LEFT,  new Surface("../client/resources/images/dying_creature_t.png", window, 1)},
                                                   {RIGHT, new Surface("../client/resources/images/dying_creature_t.png", window, 1)}

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
    loadCreaturePaths();
    loadNpcPaths();
    loadPlayerPaths();
    loadItemPaths();
    loadAttackPaths();
    loadEquippedPaths();
    createFrameSurfaces();
}
void GameSurfacesManager::createFrameSurfaces() {
    gameFrameSurface = new Surface(
            "../client/resources/images/game_frame.jpeg", window, 0);
    worldSurface = new Surface(
            "../tiled/world.png", window, 0);
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
