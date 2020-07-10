#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include "equations.h"
#include "../../common/defines/races.h"
#include "../../common/defines/classes.h"
#include "../../common/defines/creatures.h"
#include "../defines/creatures_death_drop.h"
#include "../../common/defines/items.h"

Equations::Equations(const json& config_params) :
configParams(config_params) {
    racesMap = {{HUMAN, HUMAN_STRING}, {ELF, ELF_STRING},
                 {DWARF, DWARF_STRING}, {GNOME, GNOME_STRING}};

    classesMap = {{MAGICIAN, MAGICIAN_STRING}, {CLERIC, CLERIC_STRING},
                   {PALADIN, PALADIN_STRING}, {WARRIOR, WARRIOR_STRING}};

    creaturesMap = {{GOBLIN, GOBLIN_STRING}, {SKELETON, SKELETON_STRING},
                     {ZOMBIE, ZOMBIE_STRING}, {SPIDER, SPIDER_STRING}};
}

const int Equations::eqMaxLife(Player &player) {
    std::string race_type = racesMap[player.raceType],
                class_type = classesMap[player.classType];
    json race_params = configParams["races"][race_type],
         class_params = configParams["classes"][class_type];

    double constitution = math.average(race_params["constitution"],
                                       class_params["constitution"]);
    int max_life = constitution * (int) race_params["life"] *
                   (int) class_params["life"] * player.level;
    return max_life;
}

const int Equations::eqMaxLife(Creature &creature) {
    std::string type = creaturesMap[creature.type];
    json type_params = configParams["creatures"][type];

    int max_life = (int) type_params["max_life"] + creature.level;
    return max_life;
}

const int Equations::eqInitialLife(Player &player) {
    double percentage = configParams["player"]["life"]["initial_percentage"];
    int initial_life = percentage * player.maxLife;
    return initial_life;
}

const int Equations::eqLifeRecovery(Player &player) {
    std::string race_type = racesMap[player.raceType];
    int life_recovery = (int) configParams["races"][race_type]["recovery"];
    return life_recovery;
}

const int Equations::eqMaxMana(Player &player) {
    std::string race_type = racesMap[player.raceType],
                class_type = classesMap[player.classType];
    json race_params = configParams["races"][race_type],
         class_params = configParams["classes"][class_type];

    double intelligence = math.average(race_params["intelligence"],
                                       class_params["intelligence"]);
    int max_mana = intelligence * (int) race_params["mana"] *
                   (int) class_params["mana"] * player.level;
    return max_mana;
}

const int Equations::eqInitialMana(Player &player) {
    double percentage = configParams["player"]["mana"]["initial_percentage"];
    int initial_mana = percentage * player.maxMana;
    return initial_mana;
}

const int Equations::eqManaRecovery(Player &player) {
    std::string race_type = racesMap[player.raceType];
    int mana_recovery = (int) configParams["races"][race_type]["recovery"];
    return mana_recovery;
}

const int Equations::eqManaMeditation(Player &player) {
    std::string race_type = racesMap[player.raceType],
            class_type = classesMap[player.classType];
    json race_params = configParams["races"][race_type],
            class_params = configParams["classes"][class_type];

    double intelligence = math.average(race_params["intelligence"],
                                       class_params["intelligence"]);
    int mana_recovery = (int) class_params["meditation"] * intelligence;
    return mana_recovery;
}

const int Equations::eqMaxSafeGold(Player &player) {
    json gold_params = configParams["player"]["gold"]["max_safe_eq"];
    double c1 = gold_params["c1"], c2 = gold_params["c2"];
    int max_safe_gold = c1 * pow(player.level, c2);
    return max_safe_gold;
}

const int Equations::eqMaxExcessGold(Player &player) {
    double percentage = configParams["player"]["gold"]
            ["additional_percentage"];
    int max_excess_gold = player.maxSafeGold * percentage;
    return max_excess_gold;
}

const int Equations::eqInitialGold(Player &player) {
    double percentage = configParams["player"]["gold"]["initial_percentage"];
    int initial_gold = percentage * player.maxSafeGold;
    return initial_gold;
}

const long Equations::eqExperienceLimit(const int level) {
    json exp_params = configParams["player"]["experience"]["limit_eq"];
    double c1 = exp_params["c1"], c2 = exp_params["c2"];
    long experience = c1 * pow(level, c2);
    return experience;
}

const long Equations::eqExperienceAttack(Player &player, LivingBeing &other,
        const int damage) {
    json exp_params = configParams["player"]["experience"]["attack_eq"];
    int c1 = exp_params["c1"];
    long experience = damage * std::max(other.level - player.level + c1, 0);
    return experience;
}

const long Equations::eqExperienceKill(Player &player, LivingBeing &other) {
    json exp_params = configParams["player"]["experience"]["kill_eq"];
    double c1 = exp_params["c1"], c2 = exp_params["c2"];
    int c3 = exp_params["c3"];
    long experience = math.randomDouble(c1, c2) * other.maxLife *
                      std::max(other.level - player.level + c3, 0);
    return experience;
}

const int Equations::eqDamageCaused(Player &player) {
    std::string race_type = racesMap[player.raceType],
            class_type = classesMap[player.classType];
    json race_params = configParams["races"][race_type],
            class_params = configParams["classes"][class_type];
    json attack_params = configParams["player"]["attack"]["no_weapon_eq"];

    double weapon_damage = player.weapon ?
    math.randomDouble(player.weapon->minDamage, player.weapon->maxDamage) :
    math.randomDouble(attack_params["c1"], attack_params["c2"]);

    double strength = math.average(race_params["strength"],
                                   class_params["strength"]);

    int damage = strength * weapon_damage;
    return damage;
}

const int Equations::eqDamageCaused(Creature &creature) {
    std::string type = creaturesMap[creature.type];
    json type_params = configParams["creatures"][type];

    int damage = math.randomDouble(type_params["min_attack"],
                                   type_params["max_attack"]) +
                 creature.level;
    return damage;
}

const int Equations::eqDamageReceived(Player &player, const int damage) {
    std::string race_type = racesMap[player.raceType],
            class_type = classesMap[player.classType];
    json race_params = configParams["races"][race_type],
            class_params = configParams["classes"][class_type];

    double agility = math.average(race_params["agility"],
                                  class_params["agility"]);
    json dodge_params = configParams["player"]["defense"]["dodge_eq"];
    double c1 = dodge_params["c1"], c2 = dodge_params["c2"],
           c3 = dodge_params["c3"];

    bool avoid_attack = pow(math.randomDouble(c1, c2), agility) < c3;
    if (avoid_attack)
        return 0;

    double armor_defense = player.armor ?
    math.randomDouble(player.armor->minDefense, player.armor->maxDefense) : 0;

    double helmet_defense = player.helmet ?
    math.randomDouble(player.helmet->minDefense, player.helmet->maxDefense) : 0;

    double shield_defense = player.shield ?
    math.randomDouble(player.shield->minDefense, player.shield->maxDefense) : 0;

    int defense = armor_defense + helmet_defense + shield_defense;
    int damage_received = std::max(damage - defense, 0);
    return damage_received;
}

const int Equations::eqDamageReceived(Creature &creature, const int damage) {
    std::string type = creaturesMap[creature.type];
    json type_params = configParams["creatures"][type];

    int defense = math.randomDouble(type_params["min_defense"],
                                    type_params["max_defense"]);

    int damage_received = std::max(damage - defense, 0);
    return damage_received;
}

std::vector<int> Equations::eqCreatureDeathDrop(Creature &creature) {
    std::vector<int> death_drop = {0,0};

    json js = configParams["creatures"]["death_prob_eq"];
    std::map<int, double> p = {{DROP_NOTHING, js["nothing"]["p"]},
                               {DROP_GOLD, js["gold"]["p"]},
                               {DROP_POTION, js["potion"]["p"]},
                               {DROP_ITEM, js["item"]["p"]}};

    double c1 = js["gold"]["quantity_eq"]["c1"],
           c2 = js["gold"]["quantity_eq"]["c2"],
           n = math.randomDouble(0, 1);

    int enum_drop = 0, param_drop = 0;

    if (n <= p[DROP_NOTHING]) {
        enum_drop = DROP_NOTHING;
        param_drop = 0;
    } else if (n > p[DROP_NOTHING] && n <= p[DROP_GOLD]) {
        enum_drop = DROP_GOLD;
        param_drop = math.randomDouble(c1, c2) * creature.maxLife;
    } else if (n > p[DROP_GOLD] && n <= p[DROP_POTION]) {
        enum_drop = DROP_ITEM;
        param_drop = math.randomInt(POCION_VIDA, POCION_MANA);
    } else if (n > p[DROP_POTION]) {
        enum_drop = DROP_ITEM;
        param_drop = math.randomInt(ESPADA, ESCUDO_HIERRO);
    }
    death_drop[0] = enum_drop;
    death_drop[1] = param_drop;
    return death_drop;
}
