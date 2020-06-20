#include <string>
#include <cmath>
#include "equations.h"
#include "../../common/defines/races.h"
#include "../../common/defines/classes.h"

Equations::Equations(const json& config_params) :
configParams(config_params) {
    races_map = {{HUMAN, HUMAN_STRING}, {ELF, ELF_STRING},
                 {DWARF, DWARF_STRING}, {GNOME, GNOME_STRING}};

    classes_map = {{MAGICIAN, MAGICIAN_STRING}, {CLERIC, CLERIC_STRING},
                   {PALADIN, PALADIN_STRING}, {WARRIOR, WARRIOR_STRING}};
}

const int Equations::eqMaxLife(Player &player) {
    std::string race_type = races_map[player.raceType],
                class_type = classes_map[player.classType];

    json race_params = configParams["races"][race_type],
         class_params = configParams["classes"][class_type];

    int max_life = (int) race_params["constitution"] *
                   (int) class_params["constitution"] *
                   (int) race_params["life"] *
                   (int) class_params["life"] *
                   player.level;

    return max_life;
}

const int Equations::eqInitialLife(Player &player) {
    double percentage = configParams["player"]["life"]["initial_percentage"];
    int initial_life = percentage * player.maxLife;
    return initial_life;
}

const int Equations::eqLifeRecovery(Player &player, int seconds) {
    return 0;
}

const int Equations::eqMaxMana(Player &player) {
    std::string race_type = races_map[player.raceType],
                class_type = classes_map[player.classType];
    json race_params = configParams["races"][race_type],
         class_params = configParams["classes"][class_type];

    int max_mana = (int) race_params["intelligence"] *
                   (int) class_params["intelligence"] *
                   (int) race_params["mana"] *
                   (int) class_params["mana"] *
                   player.level;
    return max_mana;
}

const int Equations::eqInitialMana(Player &player) {
    double percentage = configParams["player"]["mana"]["initial_percentage"];
    int initial_mana = percentage * player.maxMana;
    return initial_mana;
}

const int Equations::eqManaRecovery(Player &player) {
    return 0;
}

const int Equations::eqManaMeditation(Player &player) {
    return 0;
}

const int Equations::eqMaxSafeGold(Player &player) {
    json gold_params = configParams["player"]["gold"]["max_safe_eq"];
    double c1 = gold_params["c1"], c2 = gold_params["c2"];
    int max_gold = c1 * pow(player.level, c2);
    return max_gold;
}

const int Equations::eqInitialGold(Player &player) {
    double percentage = configParams["player"]["gold"]["initial_percentage"];
    int initial_gold = percentage * player.maxGold;
    return initial_gold;
}

const int Equations::eqExperienceLimit(Player &player) {
    return 0;
}

const int Equations::eqExperienceAttack(Player &player, Player &other_player) {
    return 0;
}

const int Equations::eqExperienceKill(Player &player, Player &other_player) {
    return 0;
}

const int Equations::eqAttackDamage(Player &player) {
    return 0;
}

const int Equations::eqDamageReceived(Player &player) {
    return 0;
}
