#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <string>
#include <vector>
#include <map>
#include "entities/player.h"
#include "../utilities/json.hpp"

using json = nlohmann::json;

class Equations {
    std::map<int, std::string> racesMap;
    std::map<int, std::string> classesMap;
    std::map<int, std::string> creaturesMap;
    json configParams;

    // Devuelve un numero entero aleatorio entre 'a' y 'b'
    const int randomInt(const int a, const int b);

    // Devuelve un numero double aleatorio entre 'a' y 'b'
    const double randomDouble(const double a, const double b);

    // Devuelve el promedio entre 'a' y 'b'
    const double average(const double a, const double b);

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
    const long eqExperienceLimit(Player& player);

    // Experiencia obtenida por ataque realizado a otro player
    const long eqExperienceAttack(Player& player, Player& other,
            const int damage);

    // Experiencia obtenida por ataque realizado a una criatura
    const long eqExperienceAttack(Player& player, Creature& creature,
            const int damage);

    // Experiencia obtenida por matar a otro player
    const long eqExperienceKill(Player& player, Player& other);

    // Experiencia obtenida por matar a una criatura
    const long eqExperienceKill(Player& player, Creature& creature);

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
