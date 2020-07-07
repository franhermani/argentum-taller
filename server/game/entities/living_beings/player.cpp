#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include "player.h"
#include "../../world.h"
#include "../../equations.h"
#include "../../../../common/defines/commands.h"
#include "../../../../common/defines/classes.h"
#include "../../game_exception.h"
#include "../../../../common/defines/attacks.h"

// TODO: ver si vale la pena mover esto a un param de la clase en el json
#define MOVE_VELOCITY       1500
#define RECOVERY_VELOCITY   1000
#define NO_WEAPON_VELOCITY  600
#define NO_WEAPON_RANGE     1

Player::Player(World& world, Equations& equations, const int new_id,
        const int race_type, const int class_type) :
world(world),
equations(equations),
raceType(race_type),
classType(class_type),
maxExperience(LONG_MAX),
actualExperience(0),
isMeditating(false),
isReviving(false),
ableToUseMagic(classType != WARRIOR),
weapon(nullptr),
armor(nullptr),
helmet(nullptr),
shield(nullptr),
inventory(world.getInventoryLength()),
moveVelocity(MOVE_VELOCITY),
recoveryVelocity(RECOVERY_VELOCITY),
msMoveCounter(0),
msRecoveryCounter(0),
distanceInMsToPriest(0) {
    id = new_id;
    level = 1;
    isAlive = true;
    isNewbie = (level <= world.getMaxLevelNewbie());
    orientation = DOWN;
    maxLife = equations.eqMaxLife(*this);
    actualLife = equations.eqInitialLife(*this);
    maxMana = equations.eqMaxMana(*this);
    actualMana = equations.eqInitialMana(*this);
    maxSafeGold = equations.eqMaxSafeGold(*this);
    maxExcessGold = equations.eqMaxExcessGold(*this);
    actualGold = equations.eqInitialGold(*this);

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
        "- Oro seguro maximo: " << maxSafeGold << "\n" <<
        "- Oro en exceso maximo: " << maxExcessGold << "\n" <<
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

void Player::addLife(int life) {
    actualLife += life;

    if (actualLife > maxLife)
        actualLife = maxLife;
}

void Player::subtractMana(int mana) {
    actualMana -= mana;

    if (actualMana < 0)
        actualMana = 0;
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
        if (level > world.getMaxLevelNewbie())
            isNewbie = false;
    }
}

void Player::die() {
    stopMeditating();
    isAlive = false;

    dropExcessGold();
    dropInventoryItems();
}

void Player::dropExcessGold() {
    int excess_gold = actualGold - maxSafeGold;

    if (excess_gold > 0) {
        subtractGold(excess_gold);
        world.addGold(new Gold(excess_gold, posX, posY));
    }
}

void Player::subtractGold(int gold) {
    actualGold -= gold;

    if (actualGold < 0)
        actualGold = 0;
}

void Player::dropInventoryItems() {
    // TODO: armar algun algoritmo que recorra en espiral
    /*
    int world_width = world.getWidth(), world_height = world.getHeight();
    int pos_x, pos_y, i, j, n;

    while (! inventory.isEmpty()) {
        Item* item = inventory.removeLastItem();
        if (! item)
            continue;

        i = 1, j = 1, n = 1;
        pos_x = posX, pos_y = posY;

        while ((world.inCollision(pos_x, pos_y) || world.itemInPosition(pos_x, pos_y))) {

            pos_x += i;
        }


        item->updatePosition(pos_x, pos_y);
        world.addItem(item);
    }
     */
}

void Player::stopMeditating() {
    isMeditating = false;
}

void Player::recoverLifeAndMana() {
    addLife(equations.eqLifeRecovery(*this));
    addMana(equations.eqManaRecovery(*this));

    if (isMeditating)
        addMana(equations.eqManaMeditation(*this));
}

void Player::moveNextTo(const int pos_x, const int pos_y) {
    std::vector<std::vector<int>> pos_tries =
            {{pos_x + 1, pos_y}, {pos_x - 1, pos_y},
             {pos_x, pos_y + 1}, {pos_x, pos_y - 1}};

    for (auto& pos : pos_tries) {
        if ((world.inMapBoundaries(pos[0], pos[1])) &&
        (! world.inCollision(pos[0], pos[1]))) {
            posX = pos[0];
            posY = pos[1];
            break;
        }
    }
}

void Player::equipWeapon(Weapon* new_weapon) {
    if (new_weapon->isMagic && ! ableToUseMagic) {
        inventory.addItem(new_weapon);
        throw GameException(id, "Eres un guerrero. No puedes utilizar "
                                "armas magicas");
    }
    if (weapon)
        inventory.addItem(weapon);

    weapon = new_weapon;
}

void Player::equipArmor(Armor* new_armor) {
    if (armor)
        inventory.addItem(armor);

    armor = new_armor;
}

void Player::equipHelmet(Helmet* new_helmet) {
    if (new_helmet->isMagic && ! ableToUseMagic) {
        inventory.addItem(new_helmet);
        throw GameException(id, "Eres un guerrero. No puedes utilizar "
                                "cascos magicos");
    }
    if (helmet)
        inventory.addItem(helmet);

    helmet = new_helmet;
}

void Player::equipShield(Shield* new_shield) {
    if (shield)
        inventory.addItem(shield);

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
    if (isDead()) {
        if (isReviving) {
            msMoveCounter += ms;
            if (msMoveCounter >= distanceInMsToPriest) {
                msMoveCounter = 0;
                std::vector<int> priest_pos =
                        world.getClosestPriestPos(posX, posY);
                moveNextTo(priest_pos[0], priest_pos[1]);
                shortTermRevive();
            }
        }
    } else {
        msRecoveryCounter += ms;

        if (msRecoveryCounter >= recoveryVelocity) {
            msRecoveryCounter = 0;
            recoverLifeAndMana();
        }
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

    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes curarte "
                                "antes de revivir");

    addLife(maxLife);
    addMana(maxMana);
}

void Player::shortTermRevive() {
    stopMeditating();

    if (! isDead())
        throw GameException(id, "No eres un fantasma. No puedes revivir");

    addLife(maxLife);
    isAlive = true;
    isReviving = false;
}

void Player::longTermRevive() {
    stopMeditating();

    if (! isDead())
        throw GameException(id, "No eres un fantasma. No puedes revivir");

    isReviving = true;
    distanceInMsToPriest = world.distanceInMsToClosestPriest(posX, posY,
            moveVelocity);
}

void Player::meditate() {
    if (! ableToUseMagic)
        throw GameException(id, "Eres un guerrero. No puedes meditar");

    isMeditating = isAlive;
}

void Player::attack() {
    stopMeditating();

    // TODO: chequear safe zones!!!

    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes atacar");

    int mana_consumption = weapon ? weapon->manaConsumption : 0;
    bool is_life_restorer = weapon ? weapon->isLifeRestorer : false;

    if (mana_consumption > actualMana) {
        throw GameException(id, "No tienes suficiente mana para utilizar "
                                "esta arma (requiere %d)", mana_consumption);
    } else {
        subtractMana(mana_consumption);
    }

    if (is_life_restorer) {
        addLife(maxLife);
        return;
    }

    int weapon_attack_type = weapon ? weapon->attackType : MELEE,
        weapon_range = weapon ? weapon->range : NO_WEAPON_RANGE,
        weapon_velocity = weapon ? weapon->moveVelocity : NO_WEAPON_VELOCITY;

    world.addAttack(new Attack(this, weapon_attack_type, posX, posY,
            orientation, weapon_range, weapon_velocity));
}

void Player::attack(Player& other) {
    if (other.id == id)
        return;

    if (isNewbie)
        throw GameException(id, "Eres un newbie. No puedes atacar "
                                "a otro jugador");

    if (other.isDead())
        throw GameException(id, "No puedes atacar a un jugador fantasma");

    if (other.isNewbie)
        throw GameException(id, "No puedes atacar a un jugador newbie");

    int level_diff = std::max(level - other.level, other.level - level);
    int max_level_diff = world.getMaxLevelDiff();
    if (level_diff > max_level_diff)
        throw GameException(id, "No puedes atacar a un jugador con una "
                                "diferencia de nivel mayor a %d",
                                max_level_diff);

    int damage_caused = other.receiveAttack(equations.eqDamageCaused(*this));

    addExperience(equations.eqExperienceAttack(*this, other, damage_caused));

    if (other.isDead())
        addExperience(equations.eqExperienceKill(*this, other));
}

void Player::attack(Creature &creature) {
    int damage_caused = creature.receiveAttack(
            equations.eqDamageCaused(*this));

    addExperience(equations.eqExperienceAttack(
            *this, creature, damage_caused));

    if (creature.isDead())
        addExperience(equations.eqExperienceKill(*this, creature));
}

const int Player::receiveAttack(const int damage) {
    if (isReviving)
        return 0;

    stopMeditating();

    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}

void Player::equipItemFromInventory(const int type) {
    stopMeditating();

    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes equiparte "
                                "ningun item");

    Item* item = inventory.removeItem(type);
    if (! item)
        return;

    if (dynamic_cast<Weapon*>(item)) {
        equipWeapon(dynamic_cast<Weapon*>(item));
    } else if (dynamic_cast<Armor*>(item)) {
        equipArmor(dynamic_cast<Armor*>(item));
    } else if (dynamic_cast<Helmet*>(item)) {
        equipHelmet(dynamic_cast<Helmet*>(item));
    } else if (dynamic_cast<Shield*>(item)) {
        equipShield(dynamic_cast<Shield*>(item));
    } else if (dynamic_cast<Potion*>(item)) {
        equipPotion(dynamic_cast<Potion*>(item));
    }
}

void Player::takeItemFromWorldToInventory(const int pos_x, const int pos_y) {
    stopMeditating();

    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes tomar items "
                                "del mundo");

    Item* item = world.removeItem(pos_x, pos_y);
    if (! item)
        return;

    try {
        inventory.addItem(item);
    } catch (GameException& e) {
        world.addItem(item);
        throw GameException(id, e.what());
    }
}

void Player::dropItemFromInventoryToWorld(const int type) {
    stopMeditating();

    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes tirar items "
                                "al mundo");

    if (world.itemInPosition(posX, posY))
        throw GameException(id, "Ya hay un item en esta posicion");

    Item* item = inventory.removeItem(type);
    if (! item)
        return;

    item->updatePosition(posX, posY);
    world.addItem(item);
}

Item* Player::takeItemFromInventory(const int type) {
    return inventory.removeItem(type);
}

void Player::addItemToInventory(Item *item) {
    try {
        inventory.addItem(item);
    } catch (GameException& e) {
        throw GameException(id, e.what());
    }
}

void Player::addGold(const int quant) {
    if (actualGold + quant > maxExcessGold)
        throw GameException(id, "No tienes suficiente espacio "
                                "para guardar el oro");

    actualGold += quant;
}

void Player::removeGold(const int quant) {
    if (actualGold < quant)
        throw GameException(id, "No tienes suficiente oro para extraer");

    actualGold -= quant;
}

void Player::takeGoldFromWorld(const int pos_x, const int pos_y) {
    stopMeditating();

    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes tomar oro "
                                "del mundo");

    Gold* gold = world.removeGold(pos_x, pos_y);

    try {
        addGold(gold->quantity);
    } catch (GameException& e) {
        world.addGold(gold);
        throw GameException(id, e.what());
    }
    delete gold;
}

void Player::buyItem(Item* item) {
    int item_price = item->price;
    if (item_price > actualGold) {
        delete item;
        throw GameException(id, "No tienes suficiente oro para comprar "
                                "este item");
    }
    try {
        inventory.addItem(item);
        actualGold -= item_price;
    } catch (GameException& e) {
        delete item;
        throw GameException(id, e.what());
    }
}

Item* Player::sellItem(const int type) {
    Item* item = inventory.removeItem(type);
    if (! item)
        return nullptr;

    addGold(item->price);
    return item;
}
