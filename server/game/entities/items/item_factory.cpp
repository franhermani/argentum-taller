#include "item_factory.h"

#include <utility>
#include "armor.h"
#include "helmet.h"
#include "potion.h"
#include "shield.h"
#include "weapon.h"
#include "../../../../common/defines/items.h"

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
    weapons = {ESPADA, HACHA, MARTILLO, VARA_FRESNO, FLAUTA_ELFICA,
               BACULO_NUDOSO, BACULO_ENGARZADO, ARCO_SIMPLE, ARCO_COMPUESTO};
    armors = {ARMADURA_CUERO, ARMADURA_PLACAS, TUNICA_AZUL};
    helmets = {CAPUCHA, CASCO_HIERRO, SOMBRERO_MAGICO};
    shields = {ESCUDO_TORTUGA, ESCUDO_HIERRO};
    potions = {POCION_VIDA, POCION_MANA};
}

Item* ItemFactory::operator()(const int type, const int pos_x,
        const int pos_y) {
    json js;

    if (weapons.count(type) > 0) {
        js = itemParams["weapons"][itemsMap[type]];
        return new Weapon(type, pos_x, pos_y, js["min_damage"],
                js["max_damage"], js["mana_consumption"],
                js["range"], js["move_velocity"], js["is_magic"],
                js["is_life_restorer"], js["price"]);
    } else if (armors.count(type) > 0) {
        js = itemParams["armors"][itemsMap[type]];
        return new Armor(type, pos_x, pos_y, js["min_defense"],
                js["max_defense"], js["price"]);
    } else if (helmets.count(type) > 0) {
        js = itemParams["helmets"][itemsMap[type]];
        return new Helmet(type, pos_x, pos_y, js["min_defense"],
                          js["max_defense"], js["is_magic"],
                          js["price"]);
    } else if (shields.count(type) > 0) {
        js = itemParams["shields"][itemsMap[type]];
        return new Shield(type, pos_x, pos_y, js["min_defense"],
                js["max_defense"], js["price"]);
    } else if (potions.count(type) > 0) {
        js = itemParams["potions"][itemsMap[type]];
        return new Potion(type, pos_x, pos_y, js["life_points"],
                js["mana_points"], js["price"]);
    } else {
        return nullptr;
    }
}
