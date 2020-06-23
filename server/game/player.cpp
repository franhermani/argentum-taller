#include <iostream>
#include <random>
#include <climits>
#include "player.h"
#include "world.h"
#include "equations.h"
#include "../../common/defines/commands.h"
#include "../../common/defines/classes.h"

Player::Player(World& world, Equations& equations, const int id,
        const int race_type, const int class_type) :
world(world),
equations(equations),
id(id),
raceType(race_type),
classType(class_type),
level(1),
maxExperience(LONG_MAX),
actualExperience(0),
isAlive(true),
isMeditating(false),
orientation(DOWN),
armor(0),       // TODO: enum sin armadura
helmet(0),      // TODO: enum sin casco
shield(0),      // TODO: enum sin escudo
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
        "- Pos X: " << posX << "\n" <<
        "- Pos Y: " << posY << "\n" <<
        "- Raza: " << raceType << "\n" <<
        "- Clase: " << classType << "\n" <<
        "- Vida maxima: " << maxLife << "\n" <<
        "- Vida inicial: " << actualLife << "\n" <<
        "- Mana maxima: " << maxMana << "\n" <<
        "- Mana inicial: " << actualMana << "\n" <<
        "- Oro maximo: " << maxGold << "\n" <<
        "- Oro actual: " << actualGold << "\n";
    }
}

void Player::loadInitialPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_x(0, world.getWidth() - 1);
    std::uniform_int_distribution<int> dist_y(0, world.getHeight() - 1);

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
    if (actualLife == 0) die();
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
    actualExperience += exp;
    if (actualExperience > maxExperience) actualExperience = maxExperience;
    // TODO: testear caso de subir mas de un nivel a la vez
    if (actualExperience >= equations.eqExperienceLimit(*this))
        level += 1;
}

void Player::die() {
    isAlive = false;
}

void Player::update(int ms) {
    addLife(equations.eqLifeRecovery(*this, ms));
    addMana(equations.eqManaRecovery(*this, ms));

    if (isMeditating)
        addMana(equations.eqManaMeditation(*this, ms));

    bool debug = false;
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
            new_y += 1;
            break;
        case UP:
            new_y -= 1;
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
    if (! isAlive)
        return;

    actualLife = maxLife;
    actualMana = maxMana;
    isMeditating = false;
}

void Player::revive() {
    if (isAlive)
        return;

    actualLife = maxLife;
    isAlive = true;
    isMeditating = false;
}

void Player::meditate() {
    isMeditating = (isAlive && classType != WARRIOR);
}

// TODO: contemplar NPCs
void Player::attack(int enemy_id_type, int enemy_id) {
    Player* other = world.getPlayerById(enemy_id);
    if (! other || ! other->isAlive)
        return;

    int damage_caused = other->receiveAttack(equations.eqAttackDamage(*this));
    equations.eqExperienceAttack(*this, *other, damage_caused);

    if (! other->isAlive) equations.eqExperienceKill(*this, *other);
}

const int Player::receiveAttack(const int damage) {
    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}
