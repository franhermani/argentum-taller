#include <vector>
#include <climits>
#include <algorithm>
#include "player.h"
#include "../../world.h"
#include "../../equations.h"
#include "../../../../common/defines/commands.h"
#include "../../../../common/defines/classes.h"
#include "../../game_exception.h"
#include "../../../../common/defines/attacks.h"

Player::Player(World& world, Equations& equations, json params,
        const int new_id, const int race_type, const int class_type) :
world(world),
equations(equations),
params(params),
raceType(race_type),
classType(class_type),
maxExperience(LONG_MAX),
actualExperience(0),
ableToUseMagic(classType != WARRIOR),
weapon(nullptr),
armor(nullptr),
helmet(nullptr),
shield(nullptr),
inventory(params["inventory"]["max_items"]),
moveVelocity(params["velocity"]["move"]),
recoveryVelocity(params["velocity"]["recovery"]),
msMoveCounter(0),
msRecoveryCounter(0),
distanceInMsToPriest(0) {
    id = new_id;
    level = 1;
    isNewbie = (level <= params["fair_play"]["max_level_newbie"]);
    orientation = DOWN;
    maxLife = equations.eqMaxLife(*this);
    actualLife = equations.eqInitialLife(*this);
    maxMana = equations.eqMaxMana(*this);
    actualMana = equations.eqInitialMana(*this);
    maxSafeGold = equations.eqMaxSafeGold(*this);
    maxExcessGold = equations.eqMaxExcessGold(*this);
    actualGold = equations.eqInitialGold(*this);
    state = STATE_NORMAL;
    pos = world.loadPlayerPosition();
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

    long exp_limit = equations.eqExperienceLimit(level);

    while (actualExperience >= exp_limit) {
        level ++;
        exp_limit = equations.eqExperienceLimit(level);
    }
    if (level > params["fair_play"]["max_level_newbie"])
        isNewbie = false;
}

void Player::die() {
    state = STATE_GHOST;
    dropExcessGold();
    dropInventoryItems();
}

void Player::revive() {
    state = STATE_NORMAL;
    addLife(maxLife);
}

void Player::dropExcessGold() {
    int excess_gold = actualGold - maxSafeGold;

    if (excess_gold > 0) {
        subtractGold(excess_gold);
        world.addGold(new Gold(excess_gold, pos));
    }
}

void Player::subtractGold(int gold) {
    actualGold -= gold;

    if (actualGold < 0)
        actualGold = 0;
}

void Player::dropInventoryItems() {
    position_t new_pos{};
    bool item_positioned;
    int i, j, diameter = 0, max_diameter = 10;

    while (! inventory.isEmpty()) {
        Item* item = inventory.removeLastItem();
        if (! item) continue;

        item_positioned = false;
        diameter = 1;

        while (! item_positioned) {
            for (i = pos.x - diameter; i <= pos.x + diameter; i ++) {
                for (j = pos.y - diameter; j <= pos.y + diameter; j++) {
                    new_pos.x = i;
                    new_pos.y = j;
                    if ((world.inMapBoundaries(new_pos)) &&
                       (! world.itemInCollision(new_pos))) {
                        item->updatePosition(new_pos);
                        world.addItem(item);
                        item_positioned = true;
                        break;
                    }
                }
                if (item_positioned) break;
            }
            // Sanity check to avoid big loops
            if (diameter == max_diameter)
                inventory.deleteItems();

            diameter ++;
        }
    }
}

void Player::stopMeditating() {
    if (state == STATE_MEDITATING)
        state = STATE_NORMAL;
}

const bool Player::isMeditating() const {
    return state == STATE_MEDITATING;
}

void Player::recoverLifeAndMana() {
    if (isDead())
        return;

    addLife(equations.eqLifeRecovery(*this));
    addMana(equations.eqManaRecovery(*this));

    if (isMeditating())
        addMana(equations.eqManaMeditation(*this));
}

void Player::moveNextTo(position_t new_pos) {
    std::vector<position_t> pos_tries =
            {position_t(new_pos.x + 1, new_pos.y),
             position_t(new_pos.x - 1, new_pos.y),
             position_t(new_pos.x, new_pos.y + 1),
             position_t(new_pos.x, new_pos.y - 1)};

    for (auto& pos_t : pos_tries) {
        if ((world.inMapBoundaries(pos_t)) &&
           (! world.entityInCollision(pos_t))) {
            pos = pos_t;
            break;
        }
    }
}

const int Player::secondsToRevive() {
    return (distanceInMsToPriest - msMoveCounter)/1000;
}

void Player::equipWeapon(Weapon* new_weapon) {
    if (new_weapon->isMagic && ! ableToUseMagic) {
        inventory.addItem(new_weapon);
        throw GameException(id, "Eres un guerrero. No puedes utilizar "
                                "armas magicas");
    }
    if (weapon) {
        try {
            inventory.addItem(weapon);
        } catch (GameException& e) {
            weapon->updatePosition(pos);
            world.addItem(weapon);
        }
    }
    weapon = new_weapon;
}

void Player::equipArmor(Armor* new_armor) {
    if (armor) {
        try {
            inventory.addItem(armor);
        } catch (GameException& e) {
            armor->updatePosition(pos);
            world.addItem(armor);
        }
    }
    armor = new_armor;
}

void Player::equipHelmet(Helmet* new_helmet) {
    if (new_helmet->isMagic && ! ableToUseMagic) {
        inventory.addItem(new_helmet);
        throw GameException(id, "Eres un guerrero. No puedes utilizar "
                                "cascos magicos");
    }
    if (helmet) {
        try {
            inventory.addItem(helmet);
        } catch (GameException& e) {
            helmet->updatePosition(pos);
            world.addItem(helmet);
        }
    }
    helmet = new_helmet;
}

void Player::equipShield(Shield* new_shield) {
    if (shield) {
        try {
            inventory.addItem(shield);
        } catch (GameException& e) {
            shield->updatePosition(pos);
            world.addItem(shield);
        }
    }
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
    if (isWaitingToRevive()) {
        msMoveCounter += ms;
        if (msMoveCounter >= distanceInMsToPriest) {
            msMoveCounter = 0;
            position_t priest_pos = world.getClosestPriestPos(pos);
            moveNextTo(priest_pos);
            revive();
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
    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    stopMeditating();

    position_t new_pos = pos;

    switch (direction) {
        case LEFT:
            new_pos.x -= 1;
            break;
        case RIGHT:
            new_pos.x += 1;
            break;
        case DOWN:
            new_pos.y += 1;
            break;
        case UP:
            new_pos.y -= 1;
            break;
        default:
            break;
    }
    if ((world.inMapBoundaries(new_pos)) &&
       (! world.entityInCollision(new_pos))) {
        pos = new_pos;
    }
    orientation = direction;
}

void Player::heal() {
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes curarte "
                                "antes de revivir");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    stopMeditating();

    addLife(maxLife);
    addMana(maxMana);
}

void Player::shortTermRevive() {
    if (! isDead())
        throw GameException(id, "No eres un fantasma. No puedes revivir");

    revive();
}

void Player::longTermRevive() {
    if (! isDead())
        throw GameException(id, "No eres un fantasma. No puedes revivir");

    distanceInMsToPriest = world.distanceInMsToClosestPriest(pos,
            moveVelocity);
    state = STATE_REVIVING;
}

void Player::meditate() {
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes meditar");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    if (! ableToUseMagic)
        throw GameException(id, "Eres un guerrero. No puedes meditar");

    state = STATE_MEDITATING;
}

void Player::attack() {
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes atacar");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    if (world.inSafePosition(pos))
        throw GameException(id, "No puedes atacar en una zona segura");

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
        weapon_range = weapon ? weapon->range : 1,
        weapon_velocity = weapon ? weapon->moveVelocity :
                (int) params["velocity"]["melee_attack"];

    position_t attack_pos = pos;

    switch (orientation) {
        case LEFT:
            attack_pos.x -= 1;
            break;
        case RIGHT:
            attack_pos.x += 1;
            break;
        case DOWN:
            attack_pos.y += 1;
            break;
        case UP:
            attack_pos.y -= 1;
            break;
        default:
            break;
    }

    world.addAttack(new Attack(this, weapon_attack_type, attack_pos,
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
    int max_level_diff = params["fair_play"]["max_level_diff"];

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
    if (creature.isDead())
        return;

    int damage_caused = creature.receiveAttack(
            equations.eqDamageCaused(*this));

    addExperience(equations.eqExperienceAttack(
            *this, creature, damage_caused));

    if (creature.isDead())
        addExperience(equations.eqExperienceKill(*this, creature));
}

const int Player::receiveAttack(const int damage) {
    if (isDead() || isWaitingToRevive())
        return 0;

    int damage_received = equations.eqDamageReceived(*this, damage);
    subtractLife(damage_received);
    return damage_received;
}

void Player::equipItemFromInventory(const int type) {
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes equiparte "
                                "ningun item");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    stopMeditating();

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

void Player::unequipItem(const int type) {
    try {
        switch (type) {
            case UNEQUIP_WEAPON:
                inventory.addItem(weapon);
                weapon = nullptr;
                break;
            case UNEQUIP_ARMOR:
                inventory.addItem(armor);
                armor = nullptr;
                break;
            case UNEQUIP_HELMET:
                inventory.addItem(helmet);
                helmet = nullptr;
                break;
            case UNEQUIP_SHIELD:
                inventory.addItem(shield);
                shield = nullptr;
                break;
            default:
                break;
        }
    } catch (GameException& e) {
        throw GameException(id, e.what());
    }
}

void Player::takeItemFromWorldToInventory(position_t new_pos) {
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes tomar items "
                                "del mundo");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    stopMeditating();

    Item* item = world.removeItem(new_pos);
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
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes tirar items "
                                "al mundo");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    stopMeditating();

    if (world.itemInCollision(pos))
        throw GameException(id, "Ya hay un item en esta posicion");

    Item* item = inventory.removeItem(type);
    if (! item)
        return;

    item->updatePosition(pos);
    world.addItem(item);
}

Item* Player::takeItemFromInventory(const int type) {
    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

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

const int Player::getSafeGoldSpace() {
    if (actualGold >= maxSafeGold)
        throw GameException(id, "No tienes mas espacio "
                                "para guardar oro de forma segura");

    int safe_gold_space = maxSafeGold - actualGold;
    return safe_gold_space;
}

const int Player::removeExcessGold() {
    if (actualGold <= maxSafeGold)
        throw GameException(id, "No tienes oro en exceso para depositar");

    int excess_gold = actualGold - maxSafeGold;
    subtractGold(excess_gold);
    return excess_gold;
}

void Player::takeGoldFromWorld(position_t new_pos) {
    if (isDead())
        throw GameException(id, "Eres un fantasma. No puedes tomar oro "
                                "del mundo");

    if (isWaitingToRevive())
        throw GameException(id, "No puedes ejecutar ningun comando hasta que "
                                "termines de revivir. Quedan aprox. %d "
                                "segundos", secondsToRevive());

    stopMeditating();

    Gold* gold = world.removeGold(new_pos);

    try {
        addGold(gold->quantity);
    } catch (GameException& e) {
        world.addGold(gold);
        throw e;
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

    if (item->isMagic) {
        inventory.addItem(item);
        throw GameException(id, "No se pueden vender items magicos");
    }

    try {
        addGold(item->price);
    } catch (GameException& e) {
        inventory.addItem(item);
        throw e;
    }
    return item;
}

const bool Player::isWaitingToRevive() const {
    return state == STATE_REVIVING;
}

const long Player::levelActualExperience() const {
    long prev_level_max_exp = equations.eqExperienceLimit(level - 1);
    long actual_level_exp = actualExperience;
    return actual_level_exp - prev_level_max_exp;
}

const long Player::levelMaxExperience() const {
    long prev_level_max_exp = equations.eqExperienceLimit(level - 1);
    long actual_level_max_exp = equations.eqExperienceLimit(level);
    return actual_level_max_exp - prev_level_max_exp;
}

const int Player::getId() const {
    return id;
}

position_t Player::getPos() const {
    return pos;
}
