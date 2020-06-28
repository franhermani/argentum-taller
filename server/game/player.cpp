#include <iostream>
#include <random>
#include <climits>
#include <algorithm>
#include "player.h"
#include "world.h"
#include "equations.h"
#include "../../common/defines/commands.h"
#include "../../common/defines/classes.h"
#include "game_exception.h"
#include "../../common/defines/game_exceptions.h"
#include "../../common/defines/id_types.h"

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
isNewbie(level <= world.getMinLevelNewbie()),
ableToUseMagic(classType != WARRIOR),
orientation(DOWN),
maxLife(equations.eqMaxLife(*this)),
actualLife(equations.eqInitialLife(*this)),
maxMana(equations.eqMaxMana(*this)),
actualMana(equations.eqInitialMana(*this)),
maxGold(equations.eqMaxSafeGold(*this)),
actualGold(equations.eqInitialGold(*this)),
inventory(world.getInventoryLength()) {
    loadInitialPosition();
    weapon = nullptr;
    armor = nullptr;
    helmet = nullptr;
    shield = nullptr;

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

Player::~Player() {
    delete weapon;
    delete armor;
    delete helmet;
    delete shield;
}

// --------------- //
// Private methods //
// --------------- //

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

    if (actualLife < 0)
        actualLife = 0;

    if (actualLife == 0)
        die();
}

void Player::addLife(int life) {
    actualLife += life;

    if (actualLife > maxLife)
        actualLife = maxLife;
}

void Player::addMana(int mana) {
    actualMana += mana;

    if (actualMana > maxMana)
        actualMana = maxMana;
}

void Player::addExperience(int exp) {
    actualExperience += exp;

    if (actualExperience > maxExperience)
        actualExperience = maxExperience;

    // TODO: testear caso de subir mas de un nivel a la vez
    if (actualExperience >= equations.eqExperienceLimit(*this)) {
        level += 1;
        if (level > world.getMinLevelNewbie())
            isNewbie = false;
    }
}

void Player::die() {
    stopMeditating();
    isAlive = false;
}

void Player::stopMeditating() {
    isMeditating = false;
}

void Player::equipWeapon(Weapon* new_weapon) {
    if (new_weapon->isMagic && ! ableToUseMagic)
        throw GameException(UNABLE_TO_USE_MAGIC);

    weapon = new_weapon;
}

void Player::equipArmor(Armor* new_armor) {
    armor = new_armor;
}

void Player::equipHelmet(Helmet* new_helmet) {
    if (new_helmet->isMagic && ! ableToUseMagic)
        throw GameException(UNABLE_TO_USE_MAGIC);

    helmet = new_helmet;
}

void Player::equipShield(Shield* new_shield) {
    shield = new_shield;
}

void Player::equipPotion(Potion *new_potion) {
    addLife(new_potion->lifePoints);
    addMana(new_potion->manaPoints);
    delete new_potion;
}

// -------------- //
// Public methods //
// -------------- //

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
    stopMeditating();

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
}

void Player::heal() {
    stopMeditating();

    if (! isAlive)
        throw GameException(UNABLE_TO_INTERACT);

    actualLife = maxLife;
    actualMana = maxMana;
}

void Player::revive() {
    stopMeditating();

    if (isAlive)
        throw GameException(UNABLE_TO_REVIVE);

    actualLife = maxLife;
    isAlive = true;
}

void Player::meditate() {
    if (! ableToUseMagic)
        throw GameException(UNABLE_TO_MEDITATE);

    isMeditating = isAlive;
}

// TODO: contemplar NPCs
// TODO: testear todos los casos de esta funcion
void Player::attack(int enemy_id_type, int enemy_id) {
    stopMeditating();

    if (! isAlive)
        throw GameException(UNABLE_TO_INTERACT);

    if (isNewbie && enemy_id_type == ID_PLAYER)
        throw GameException(NEWBIE_ATTACK_FORBIDDEN);

    Player* other = world.getPlayerById(enemy_id);
    if (! other || ! other->isAlive)
        throw GameException(UNABLE_TO_ATTACK_DEAD_PLAYER);

    if (other->isNewbie)
        throw GameException(NEWBIE_ATTACK_FORBIDDEN);

    int level_diff = std::max(level - other->level, other->level - level);
    if (level_diff > world.getMinLevelDiff())
        throw GameException(DIFF_LEVEL_ATTACK_FORBIDDEN);

    int damage_caused = other->receiveAttack(equations.eqDamageCaused(*this));
    equations.eqExperienceAttack(*this, *other, damage_caused);

    if (! other->isAlive)
        equations.eqExperienceKill(*this, *other);
}

const int Player::receiveAttack(const int damage) {
    stopMeditating();

    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}

// TODO: testear esta funcion
void Player::equipItemFromInventory(const int type) {
    stopMeditating();

    if (! isAlive)
        throw GameException(UNABLE_TO_INTERACT);

    Item* item = inventory.removeItem(type);
    if (typeid(item) == typeid(Weapon)) {
        equipWeapon(dynamic_cast<Weapon*>(item));
    } else if (typeid(item) == typeid(Armor)) {
        equipArmor(dynamic_cast<Armor*>(item));
    } else if (typeid(item) == typeid(Helmet)) {
        equipHelmet(dynamic_cast<Helmet*>(item));
    } else if (typeid(item) == typeid(Shield)) {
        equipShield(dynamic_cast<Shield*>(item));
    } else if (typeid(item) == typeid(Potion)) {
        equipPotion(dynamic_cast<Potion*>(item));
    }
}

void Player::takeItemFromWorldToInventory(const int pos_x, const int pos_y) {
    stopMeditating();

    if (! isAlive)
        throw GameException(UNABLE_TO_INTERACT);


    Item* item = world.removeItem(pos_x, pos_y);
    if (item) inventory.addItem(item);
}

void Player::dropItemFromInventoryToWorld(const int type) {
    stopMeditating();

    if (! isAlive)
        throw GameException(UNABLE_TO_INTERACT);

    if (world.itemInPosition(posX, posY))
        throw GameException(ITEM_IN_POSITION);

    Item* item = inventory.removeItem(type);
    item->updatePosition(posX, posY);
    world.addItem(item);
}
