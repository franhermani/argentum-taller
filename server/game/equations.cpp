#include "equations.h"
#include "../../common/defines/classes.h"
#include "../../common/defines/races.h"

Equations::Equations(const json& config_params) :
configParams(config_params) {}

const int Equations::eqMaxLife(Player &player) {
    return 0;
}

const int Equations::eqLifeRecovery(Player &player, int seconds) {
    return 0;
}

const int Equations::eqMaxMana(Player &player) {
    return 0;
}

const int Equations::eqManaRecovery(Player &player) {
    return 0;
}

const int Equations::eqManaMeditation(Player &player) {
    return 0;
}

const int Equations::eqMaxSafeGold(Player &player) {
    return 0;
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
