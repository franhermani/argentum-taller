#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <string>
#include <vector>
#include <map>
#include "../utilities/json.hpp"
#include "../utilities/math_calculator.h"
#include "entities/living_beings/player.h"

using json = nlohmann::json;

class Equations {
    json configParams;
    Math math;
    std::map<int, std::string> creaturesMap;
    std::map<int, std::string> racesMap;
    std::map<int, std::string> classesMap;

public:
    // Constructor
    explicit Equations(const json& config_params);

    // Constructor y asignacion por copia deshabilitados
    Equations(const Equations& other) = delete;
    Equations& operator=(const Equations& other) = delete;

    // Vida maxima del player
    const int eqMaxLife(Player& player);

    // Vida maxima de la criatura
    const int eqMaxLife(Creature& creature);

    // Vida inicial
    const int eqInitialLife(Player& player);

    // Recuperacion de vida por el paso del tiempo
    const int eqLifeRecovery(Player& player);

    // Mana maxima
    const int eqMaxMana(Player& player);

    // Mana inicial
    const int eqInitialMana(Player& player);

    // Recuperacion de mana por el paso del tiempo
    const int eqManaRecovery(Player& player);

    // Recuperacion de mana por meditar
    const int eqManaMeditation(Player& player);

    // Oro seguro en mano maximo
    const int eqMaxSafeGold(Player& player);

    // Oro en exceso maximo
    const int eqMaxExcessGold(Player& player);

    // Oro inicial
    const int eqInitialGold(Player& player);

    // Limite de experiencia del nivel actual
    const long eqExperienceLimit(const int level);

    // Experiencia obtenida por ataque realizado a otro player o criatura
    const long eqExperienceAttack(Player& player, LivingBeing& other,
            const int damage);

    // Experiencia obtenida por matar a otro player o criatura
    const long eqExperienceKill(Player& player, LivingBeing& other);

    // Daño producido por ataque realizado de un player
    const int eqDamageCaused(Player& player);

    // Daño producido por ataque realizado de una criatura
    const int eqDamageCaused(Creature& creature);

    // Daño recibido de player por ataque recibido
    // Incluye la posibilidad de esquivarlo
    const int eqDamageReceived(Player& player, const int damage);

    // Daño recibido de criatura por ataque recibido
    // Incluye la posibilidad de esquivarlo
    const int eqDamageReceived(Creature& creature, const int damage);

    // Item o cantidad de oro que dropea una criatura al morir
    // Devuelve un vector<enum creatureDeathDrop, cant o enum itemType>
    std::vector<int> eqCreatureDeathDrop(Creature& creature);
};

#endif // EQUATIONS_H
