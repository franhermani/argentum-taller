#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <string>
#include <map>
#include "entities/player.h"
#include "../utilities/json.hpp"

using json = nlohmann::json;

class Equations {
    std::map<int, std::string> races_map;
    std::map<int, std::string> classes_map;
    std::map<int, std::string> creatures_map;
    json configParams;

    // Devuelve un numero aleatorio entre 'a' y 'b'
    const double randomNumber(const double a, const double b);

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
    const int eqLifeRecovery(Player& player, int ms);

    // Mana maxima
    const int eqMaxMana(Player& player);

    // Mana inicial
    const int eqInitialMana(Player& player);

    // Recuperacion de mana por el paso del tiempo
    const int eqManaRecovery(Player& player, int ms);

    // Recuperacion de mana por meditar
    const int eqManaMeditation(Player& player, int ms);

    // Oro seguro en mano maximo
    const int eqMaxSafeGold(Player& player);

    // Oro inicial
    const int eqInitialGold(Player& player);

    // Oro que dropea una criatura al morir
//    const int eqGoldDrop(NPC& npc);

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
};

#endif // EQUATIONS_H
