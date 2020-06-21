#include <iostream>
#include <random>
#include "player.h"
#include "world.h"
#include "equations.h"
#include "../../common/defines/commands.h"

Player::Player(World& world, Equations& equations, const int id,
        const int race_type, const int class_type) :
world(world),
equations(equations),
id(id),
raceType(race_type),
classType(class_type),
experience(0),
level(1),
isAlive(true),
isMeditating(false),
orientation(DOWN),
bodyArmor(0),   // TODO: enum sin armadura
headArmor(0),   // TODO: enum sin armadura
weapon(0),      // TODO: enum sin arma
maxLife(equations.eqMaxLife(*this)),
actualLife(equations.eqInitialLife(*this)),
maxMana(equations.eqMaxMana(*this)),
actualMana(equations.eqInitialMana(*this)),
maxGold(equations.eqMaxSafeGold(*this)),
actualGold(equations.eqInitialGold(*this)) {
    loadInitialPosition();

    bool debug = true;
    if (debug) {
        std::cout << "Player " << id << " creado!\n" <<
        "- Raza: " << raceType << "\n" <<
        "- Clase: " << classType << "\n" <<
        "- Vida maxima: " << maxLife << "\n" <<
        "- Vida inicial: " << actualLife << "\n" <<
        "- Mana maxima: " << maxMana << "\n" <<
        "- Mana inicial: " << actualMana << "\n" <<
        "- Oro maximo: " << maxGold << "\n" <<
        "- Oro actual: " << actualGold << "\n";

        int exp1 = equations.eqExperienceLimit(*this);
        int exp2 = equations.eqExperienceAttack(*this, *this);
        int exp3 = equations.eqExperienceKill(*this, *this);

        std::cout << "Limite de experiencia: " << exp1 << "\n" <<
                  "Experiencia por ataque: " << exp2 << "\n" <<
                  "Experiencia por matar: " << exp3 << "\n";
    }
}

void Player::loadInitialPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, world.getWidth());
    std::uniform_int_distribution<int> dist_y(0, world.getHeight());

    int new_x = dist_x(mt), new_y = dist_y(mt);
    while (world.inCollision(new_x, new_y)) {
        new_x = dist_x(mt);
        new_y = dist_y(mt);
    }
    posX = new_x;
    posY = new_y;
}

void Player::subtractLife(int life) {
    actualLife -= life;
    if (actualLife < 0) actualLife = 0;
    if (actualLife == 0) isAlive = false;
}

void Player::addLife(int life) {
    actualLife += life;
    if (actualLife > maxLife) actualLife = maxLife;
}

void Player::addMana(int mana) {
    actualMana += mana;
    if (actualMana > maxMana) actualMana = maxMana;
}

void Player::addExperience(int exp) {
    experience += exp;
    // TODO: testear caso de subir mas de un nivel a la vez
    if (experience >= equations.eqExperienceLimit(*this))
        level += 1;
}

void Player::update(int ms) {
    addLife(equations.eqLifeRecovery(*this, ms/1000));
    addMana(equations.eqManaRecovery(*this, ms/1000));

    if (isMeditating)
        addMana(equations.eqManaMeditation(*this, ms/1000));

    bool debug = true;
    if (debug) {
        std::cout << "Ms transcurridos: " << ms << "\n" <<
                     "Vida actual: " << actualLife << "\n" <<
                     "Mana actual: " << actualMana << "\n";
    }
}

void Player::moveTo(int direction) {
    int new_x = posX, new_y = posY;
    switch (direction) {
        case LEFT:
            new_x -= 1;
            break;
        case RIGHT:
            new_x += 1;
            break;
        case DOWN:
            new_y -= 1;
            break;
        case UP:
            new_y += 1;
            break;
        default:
            break;
    }
    if ((world.inMapBoundaries(new_x, new_y)) &&
        (! world.inCollision(new_x, new_y))) {
        posX = new_x;
        posY = new_y;
    }
    orientation = direction;
    isMeditating = false;
}

void Player::heal() {
    actualLife = maxLife;
    actualMana = maxMana;
    isMeditating = false;
}

void Player::revive() {
    actualLife = maxLife;
    isAlive = true;
    isMeditating = false;
}

void Player::meditate() {
    isMeditating = true;
}
