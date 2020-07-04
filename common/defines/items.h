#ifndef ITEMS_H
#define ITEMS_H

#define ESPADA_STRING               "espada"
#define HACHA_STRING                "hacha"
#define MARTILLO_STRING             "martillo"
#define VARA_FRESNO_STRING          "vara_fresno"
#define FLAUTA_ELFICA_STRING        "flauta_elfica"
#define BACULO_NUDOSO_STRING        "baculo_nudoso"
#define BACULO_ENGARZADO_STRING     "baculo_engarzado"
#define ARCO_SIMPLE_STRING          "arco_simple"
#define ARCO_COMPUESTO_STRING       "arco_compuesto"
#define ARMADURA_CUERO_STRING       "armadura_cuero"
#define ARMADURA_PLACAS_STRING      "armadura_placas"
#define TUNICA_AZUL_STRING          "tunica_azul"
#define CAPUCHA_STRING              "capucha"
#define CASCO_HIERRO_STRING         "casco_hierro"
#define SOMBRERO_MAGICO_STRING      "sombrero_magico"
#define ESCUDO_TORTUGA_STRING       "escudo_tortuga"
#define ESCUDO_HIERRO_STRING        "escudo_hierro"
#define POCION_VIDA_STRING          "pocion_vida"
#define POCION_MANA_STRING          "pocion_mana"

enum itemType {
    // No item equipped
    NO_ITEM_EQUIPPED,

    // Weapons
    ESPADA,
    HACHA,
    MARTILLO,
    VARA_FRESNO,
    FLAUTA_ELFICA,
    BACULO_NUDOSO,
    BACULO_ENGARZADO,
    ARCO_SIMPLE,
    ARCO_COMPUESTO,

    // Armor
    ARMADURA_CUERO,
    ARMADURA_PLACAS,
    TUNICA_AZUL,

    // Helmet
    CAPUCHA,
    CASCO_HIERRO,
    SOMBRERO_MAGICO,

    // Shield
    ESCUDO_TORTUGA,
    ESCUDO_HIERRO,

    // Potion
    POCION_VIDA,
    POCION_MANA
};

#endif // ITEMS_H
