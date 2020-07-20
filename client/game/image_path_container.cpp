
#include "image_path_container.h"


ImagePathContainer::ImagePathContainer() {
    loadCreaturePaths();
    loadNpcPaths();
    loadPlayerPaths();
    loadItemPaths();
    loadAttackPaths();
    loadEquippedPaths();
    loadAnimatedPaths();
}

void ImagePathContainer::loadCreaturePaths() {
    //CRIATURAS
    std::map<int, std::string> skeleton_orientations = {
            {UP,   "../client/resources/images/characters/skeleton_up_t.png"},
            {DOWN, "../client/resources/images/characters/skeleton_down_t.png"},
            {LEFT, "../client/resources/images/characters/skeleton_left_t.png"},
            {RIGHT,
                   "../client/resources/images/characters/skeleton_right_t.png"}
    };
    std::map<int, std::string> goblin_orientations = {
            {UP,    "../client/resources/images/characters/goblin_up_t.png"},
            {DOWN,  "../client/resources/images/characters/goblin_down_t.png"},
            {LEFT,  "../client/resources/images/characters/goblin_left_t.png"},
            {RIGHT, "../client/resources/images/characters/goblin_right_t.png"}
    };

    std::map<int, std::string> zombie_orientations = {
            {UP,    "../client/resources/images/characters/zombie_up_t.png"},
            {DOWN,  "../client/resources/images/characters/zombie_down_t.png"},
            {LEFT,  "../client/resources/images/characters/zombie_left_t.png"},
            {RIGHT, "../client/resources/images/characters/zombie_right_t.png"}
    };
    std::map<int, std::string> spider_orientations = {
            {UP,    "../client/resources/images/characters/spider_up_t.png"},
            {DOWN,  "../client/resources/images/characters/spider_down_t.png"},
            {LEFT,  "../client/resources/images/characters/spider_left_t.png"},
            {RIGHT, "../client/resources/images/characters/spider_right_t.png"}
    };


    creatureSurfacesPaths = {
            {SKELETON, skeleton_orientations},
            {ZOMBIE,   zombie_orientations},
            {GOBLIN,   goblin_orientations},
            {SPIDER,   spider_orientations}
    };
}

void ImagePathContainer::loadAnimatedPaths() {
    animatedStatePaths = {
            {STATE_MEDITATING,
                    "../client/resources/images/characters/meditating_anim_t.png"},
            {STATE_REVIVING,
                    "../client/resources/images/characters/reviving_anim_t.png"},
    };
}
void ImagePathContainer::loadEquippedPaths() {
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
            {UP,    "../client/resources/images/weapons/espada_up_p_t.png"},
            {DOWN,  "../client/resources/images/weapons/espada_down_p_t.png"},
            {LEFT,  "../client/resources/images/weapons/espada_right_p_t.png"},
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
            {UP,    "../client/resources/images/weapons/hacha_up_p_t.png"},
            {DOWN,  "../client/resources/images/weapons/hacha_down_p_t.png"},
            {LEFT,  "../client/resources/images/weapons/hacha_right_p_t.png"},
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
            {UP,    "../client/resources/images/items/tunica_azul_up_t.png"},
            {DOWN,  "../client/resources/images/items/tunica_azul_down_t.png"},
            {LEFT,  "../client/resources/images/items/tunica_azul_left_t.png"},
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
            {UP,    "../client/resources/images/items/capucha_up_t.png"},
            {DOWN,  "../client/resources/images/items/capucha_down_t.png"},
            {LEFT,  "../client/resources/images/items/capucha_left_t.png"},
            {RIGHT, "../client/resources/images/items/capucha_right_t.png"}
    };
    std::map<int, std::string> casco_hierro_orientations = {
            {UP,    "../client/resources/images/items/casco_hierro_up_t.png"},
            {DOWN,  "../client/resources/images/items/casco_hierro_down_t.png"},
            {LEFT,  "../client/resources/images/items/casco_hierro_right_t.png"},
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
            {ESPADA,          espada_orientations},
            {HACHA,           hacha_orientations},
            {MARTILLO,        martillo_orientations},
            {VARA_FRESNO,     baculo_orientations},
            {FLAUTA_ELFICA,   flauta_elfica_orientations},
            {BACULO_NUDOSO,   baculo_orientations},
            {BACULO_ENGARZADO,
                              baculo_engarzado_orientations},
            {ARCO_SIMPLE,     arco_simple_orientations},
            {ARCO_COMPUESTO,
                              arco_compuesto_orientations},
            {ESCUDO_HIERRO,   escudo_hierro_orientations},
            {ESCUDO_TORTUGA,  escudo_tortuga_orientations},
            {ARMADURA_CUERO,  armadura_cuero_orientations},
            {ARMADURA_PLACAS, armadura_placas_orientations},
            {TUNICA_AZUL,     tunica_azul_orientations},
            {CASCO_HIERRO,    casco_hierro_orientations},
            {CAPUCHA,         capucha_orientations},
            {SOMBRERO_MAGICO, sombrero_magico_orientations}
    };
}


void ImagePathContainer::loadNpcPaths() {
    //npcs
    std::map<int, std::string> banker_orientations = {
            {UP,    "../client/resources/images/characters/banker_up_t.png"},
            {DOWN,  "../client/resources/images/characters/banker_down_t.png"},
            {LEFT,  "../client/resources/images/characters/banker_left_t.png"},
            {RIGHT, "../client/resources/images/characters/banker_right_t.png"}
    };
    std::map<int, std::string> priest_orientations = {
            {UP,    "../client/resources/images/characters/priest_up_t.png"},
            {DOWN,  "../client/resources/images/characters/priest_down_t.png"},
            {LEFT,  "../client/resources/images/characters/priest_left_t.png"},
            {RIGHT, "../client/resources/images/characters/priest_right_t.png"}
    };
    std::map<int, std::string> merchant_orientations = {
            {UP,   "../client/resources/images/characters/merchant_up_t.png"},
            {DOWN, "../client/resources/images/characters/merchant_down_t.png"},
            {LEFT, "../client/resources/images/characters/merchant_left_t.png"},
            {RIGHT,
                   "../client/resources/images/characters/merchant_right_t.png"}
    };

    npcSurfacesPaths = {
            {PRIEST,   priest_orientations},
            {MERCHANT, merchant_orientations},
            {BANKER,   {banker_orientations}}
    };
}

void ImagePathContainer::loadAttackPaths() {
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
            {UP,   "../client/resources/images/attacks/magic_arrow_up_t.png"},
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
            {UP,    "../client/resources/images/attacks/melee_attack_t_big.png"},
            {DOWN,  "../client/resources/images/attacks/melee_attack_t_big.png"},
            {LEFT,  "../client/resources/images/attacks/melee_attack_t_big.png"},
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
            {UP,    "../client/resources/images/attacks/missile_up_t.png"},
            {DOWN,  "../client/resources/images/attacks/missile_down_t.png"},
            {LEFT,  "../client/resources/images/attacks/missile_left_t.png"},
            {RIGHT, "../client/resources/images/attacks/missile_right_t.png"}
    };

    std::map<int, std::string> explosion_spell_orientations = {
            {UP,    "../client/resources/images/attacks/explosion_t.png"},
            {DOWN,  "../client/resources/images/attacks/explosion_t.png"},
            {LEFT,  "../client/resources/images/attacks/explosion_t.png"},
            {RIGHT, "../client/resources/images/attacks/explosion_t.png"}
    };

    std::map<int, std::string> heal_spell_orientations = {
            {UP,    "../client/resources/images/attacks/heal_t.png"},
            {DOWN,  "../client/resources/images/attacks/heal_t.png"},
            {LEFT,  "../client/resources/images/attacks/heal_t.png"},
            {RIGHT, "../client/resources/images/attacks/heal_t.png"}
    };

    attackSurfacesPaths = {
            {MULTIPLE_ARROW,    multiple_arrow_orientations},
            {SINGLE_ARROW,      single_arrow_orientations},
            {MELEE,             melee_orientations},
            {NO_WEAPON_MELEE,   no_weapon_melee_orientations},
            {MAGIC_ARROW_SPELL, magic_arrow_orientations},
            {HEAL_SPELL,        heal_spell_orientations},
            {MISSILE_SPELL,     missile_orientations},
            {EXPLOSION_SPELL,   explosion_spell_orientations}
    };
}


void ImagePathContainer::loadPlayerPaths() {
    //JUGADORES

    std::map<int, std::string> human_orientations = {
            {UP,    "../client/resources/images/characters/human_up_t.png"},
            {DOWN,  "../client/resources/images/characters/human_down_t.png"},
            {LEFT,  "../client/resources/images/characters/human_left_t.png"},
            {RIGHT, "../client/resources/images/characters/human_right_t.png"}
    };
    std::map<int, std::string> elf_orientations = {
            {UP,    "../client/resources/images/characters/elf_up_t.png"},
            {DOWN,  "../client/resources/images/characters/elf_down_t.png"},
            {LEFT,  "../client/resources/images/characters/elf_left_t.png"},
            {RIGHT, "../client/resources/images/characters/elf_right_t.png"}
    };
    std::map<int, std::string> dwarf_orientations = {
            {UP,    "../client/resources/images/characters/dwarf_up_t.png"},
            {DOWN,  "../client/resources/images/characters/dwarf_down_t.png"},
            {LEFT,  "../client/resources/images/characters/dwarf_left_t.png"},
            {RIGHT, "../client/resources/images/characters/dwarf_right_t.png"}
    };
    std::map<int, std::string> gnome_orientations = {
            {UP,    "../client/resources/images/characters/gnome_up_t.png"},
            {DOWN,  "../client/resources/images/characters/gnome_down_t.png"},
            {LEFT,  "../client/resources/images/characters/gnome_left_t.png"},
            {RIGHT, "../client/resources/images/characters/gnome_right_t.png"}
    };
    playerSurfacesPaths = {
            {HUMAN, human_orientations},
            {ELF,   elf_orientations},
            {DWARF, dwarf_orientations},
            {GNOME, gnome_orientations}
    };
}



void ImagePathContainer::loadItemPaths() {
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