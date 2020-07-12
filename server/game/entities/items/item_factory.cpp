#include "item_factory.h"

#include <utility>
#include "armor.h"
#include "helmet.h"
#include "potion.h"
#include "shield.h"
#include "weapon.h"
#include "../../../../common/defines/items.h"
#include "../../../../common/defines/attacks.h"

ItemFactory::ItemFactory(json item_params) :
itemParams(std::move(item_params)) {
    itemsMap = {{ESPADA, ESPADA_STRING},
                {HACHA, HACHA_STRING},
                {MARTILLO, MARTILLO_STRING},
                {VARA_FRESNO, VARA_FRESNO_STRING},
                {FLAUTA_ELFICA, FLAUTA_ELFICA_STRING},
                {BACULO_NUDOSO, BACULO_NUDOSO_STRING},
                {BACULO_ENGARZADO, BACULO_ENGARZADO_STRING},
                {ARCO_SIMPLE, ARCO_SIMPLE_STRING},
                {ARCO_COMPUESTO, ARCO_COMPUESTO_STRING},
                {ARMADURA_CUERO, ARMADURA_CUERO_STRING},
                {ARMADURA_PLACAS, ARMADURA_PLACAS_STRING},
                {TUNICA_AZUL, TUNICA_AZUL_STRING},
                {CAPUCHA, CAPUCHA_STRING},
                {CASCO_HIERRO, CASCO_HIERRO_STRING},
                {SOMBRERO_MAGICO, SOMBRERO_MAGICO_STRING},
                {ESCUDO_TORTUGA, ESCUDO_TORTUGA_STRING},
                {ESCUDO_HIERRO, ESCUDO_HIERRO_STRING},
                {POCION_VIDA, POCION_VIDA_STRING},
                {POCION_MANA, POCION_MANA_STRING}};

    attackTypesMap = {{MELEE_STRING, MELEE},
                      {MAGIC_ARROW_SPELL_STRING, MAGIC_ARROW_SPELL},
                      {HEAL_SPELL_STRING, HEAL_SPELL},
                      {MISSILE_SPELL_STRING, MISSILE_SPELL},
                      {EXPLOSION_SPELL_STRING, EXPLOSION_SPELL},
                      {SINGLE_ARROW_STRING, SINGLE_ARROW},
                      {MULTIPLE_ARROW_STRING, MULTIPLE_ARROW}};

    weapons = {ESPADA, HACHA, MARTILLO, VARA_FRESNO, FLAUTA_ELFICA,
               BACULO_NUDOSO, BACULO_ENGARZADO, ARCO_SIMPLE, ARCO_COMPUESTO};
    armors = {ARMADURA_CUERO, ARMADURA_PLACAS, TUNICA_AZUL};
    helmets = {CAPUCHA, CASCO_HIERRO, SOMBRERO_MAGICO};
    shields = {ESCUDO_TORTUGA, ESCUDO_HIERRO};
    potions = {POCION_VIDA, POCION_MANA};
}

Item* ItemFactory::operator()(const int type, position_t new_pos) {
    json js;

    if (weapons.count(type) > 0) {
        js = itemParams["weapons"][itemsMap[type]];
        return new Weapon(type, attackTypesMap[js["attack_type"]],
                new_pos,js["min_damage"],js["max_damage"],
                js["mana_consumption"],js["range"],
                js["move_velocity"], js["is_magic"],
                js["is_life_restorer"], js["price"]);
    } else if (armors.count(type) > 0) {
        js = itemParams["armors"][itemsMap[type]];
        return new Armor(type, new_pos, js["min_defense"],
                js["max_defense"], js["is_magic"], js["price"]);
    } else if (helmets.count(type) > 0) {
        js = itemParams["helmets"][itemsMap[type]];
        return new Helmet(type, new_pos, js["min_defense"],
                          js["max_defense"], js["is_magic"],
                          js["price"]);
    } else if (shields.count(type) > 0) {
        js = itemParams["shields"][itemsMap[type]];
        return new Shield(type, new_pos, js["min_defense"],
                js["max_defense"], js["is_magic"], js["price"]);
    } else if (potions.count(type) > 0) {
        js = itemParams["potions"][itemsMap[type]];
        return new Potion(type, new_pos, js["life_points"],
                js["mana_points"], js["is_magic"], js["price"]);
    } else {
        return nullptr;
    }
}

const int ItemFactory::getItemPrice(const int type) {
    json js;
    int price = 0;

    if (weapons.count(type) > 0) {
        price = itemParams["weapons"][itemsMap[type]]["price"];
    } else if (armors.count(type) > 0) {
        price = itemParams["armors"][itemsMap[type]]["price"];
    } else if (helmets.count(type) > 0) {
        price = itemParams["helmets"][itemsMap[type]]["price"];
    } else if (shields.count(type) > 0) {
        price = itemParams["shields"][itemsMap[type]]["price"];
    } else if (potions.count(type) > 0) {
        price = itemParams["potions"][itemsMap[type]]["price"];
    }
    return price;
}
