#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <string>
#include <map>
#include "player.h"
#include "../utilities/json.hpp"

using json = nlohmann::json;

class Equations {
    std::map<int, std::string> races_map;
    std::map<int, std::string> classes_map;
    json configParams;

public:
    // Constructor
    explicit Equations(const json& config_params);

    // Constructor y asignacion por copia deshabilitados
    Equations(const Equations& other) = delete;
    Equations& operator=(const Equations& other) = delete;

    // Vida maxima
    const int eqMaxLife(Player& player);

    // Recuperacion de vida por el paso del tiempo
    const int eqLifeRecovery(Player& player, int seconds);

    // Mana maxima
    const int eqMaxMana(Player& player);

    // Recuperacion de mana por el paso del tiempo
    const int eqManaRecovery(Player& player);

    // Recuperacion de mana por meditar
    const int eqManaMeditation(Player& player);

    // Oro que dropea un NPC al morir
//    const int eqGoldDrop(NPC& npc);

    // Oro seguro en mano maximo
    const int eqMaxSafeGold(Player& player);

    // Limite de experiencia del nivel actual
    const int eqExperienceLimit(Player& player);

    // Experiencia obtenida por ataque realizado
    const int eqExperienceAttack(Player& player, Player& other_player);
//    const int eqExperienceAttack(Player& player, NPC& npc);

    // Experiencia obtenida por matar a un enemigo
    const int eqExperienceKill(Player& player, Player& other_player);
//    const int eqExperienceKill(Player& player, NPC& npc);

    // Daño producido por ataque realizado
    const int eqAttackDamage(Player& player);

    // Daño recibido por ataque recibido (incluye la posibilidad de esquivarlo)
    const int eqDamageReceived(Player& player);
};

#endif // EQUATIONS_H
