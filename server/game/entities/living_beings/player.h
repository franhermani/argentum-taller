#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "living_being.h"
#include "../../../../common/defines/states.h"
#include "../items/weapon.h"
#include "../items/armor.h"
#include "../items/helmet.h"
#include "../items/shield.h"
#include "../items/potion.h"
#include "../items/inventory.h"
#include "creature.h"
#include "../../../utilities/json_parser.h"

class World;
class Equations;

class Player : public LivingBeing {
    World& world;
    Equations& equations;
    json params;
    int raceType;
    int classType;
    long maxExperience;
    long actualExperience;
    bool isNewbie;
    bool ableToUseMagic;
    bool isWaitingToMove;
    int nextDirection;
    int maxMana;
    int actualMana;
    int maxSafeGold;
    int maxExcessGold;
    int actualGold;
    Weapon* weapon;
    Armor* armor;
    Helmet* helmet;
    Shield* shield;
    Inventory inventory;
    int moveVelocity, recoveryVelocity;
    int msMoveCounter, msRecoveryCounter;
    int distanceInMsToPriest;

    friend class Equations;
    friend class ServerProtocol;

    // Suma puntos de vida al player
    void addLife(int life);

    // Resta puntos de mana al player
    void subtractMana(int mana);

    // Suma puntos de mana al player
    void addMana(int mana);

    // Suma puntos de experiencia al player
    // Si llega al limite, sube de nivel
    void addExperience(int exp);

    // Cambia el estado a fantasma y dropea oro e items del inventario
    virtual void die() override;

    // Revive al player
    void revive();

    // Dropea el oro en exceso al mundo
    void dropExcessGold();

    // Resta 'gold' cantidad de oro al player
    void subtractGold(int gold);

    // Dropea los items del inventario al mundo
    void dropInventoryItems();

    // Devuelve true si esta meditando, false en caso contrario
    const bool isMeditating() const;

    // Recupera vida y mana por el paso del tiempo
    void recoverLifeAndMana();

    // Mueve al player segun la ultima direccion recibida
    void moveTo();

    // Mueve al player al lado de la posicion (x,y)
    void moveNextTo(position_t new_pos);

    // Asigna 'new_weapon' a 'weapon'
    void equipWeapon(Weapon* new_weapon);

    // Asigna 'new_armor' a 'armor'
    void equipArmor(Armor* new_armor);

    // Asigna 'new_helmet' a 'helmet'
    void equipHelmet(Helmet* new_helmet);

    // Asigna el 'new_shield' a 'shield'
    void equipShield(Shield* new_shield);

    // Suma los puntos de vida y mana correspondientes segun la pocion
    void equipPotion(Potion* new_potion);

public:
    // Constructor
    Player(World& world, Equations& equations, json params, const int new_id,
            const int race_type, const int class_type);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // Destructor
    // Libera la memoria reservada para los items que esten equipados
    ~Player();

    // Recupera vida y mana con el paso del tiempo
    // Recupera mana con el estado de meditacion
    virtual void update(int ms) override;

    // Mueve el player segun la direccion dada
    void moveTo(int direction);

    // Recupera todos los puntos de vida y mana del player
    void heal();

    // Revive al player de forma inmediata
    void shortTermRevive();

    // Saca el estado de reviviendo
    void longTermRevive();

    // El player entra en estado de meditacion
    void meditate();

    // Saca el estado de meditando
    void stopMeditating();

    // Realiza un ataque en la orientacion del player
    void attack();

    // Ataca a otro player
    void attack(Player& other) override;

    // Ataca a una criatura
    void attack(Creature& creature) override;

    // Recibe el ataque de otro player o criatura
    // Devuelve la cantidad de daño realmente recibido
    const int receiveAttack(const int damage) override;

    // Saca un item del inventario segun 'type' y lo equipa
    void equipItemFromInventory(const int type);

    // Saca un item equipado y lo guarda en el inventario
    void unequipItem(const int type);

    // Saca un item del mundo segun su pos (x,y) y lo guarda en el inventario
    void takeItemFromWorldToInventory(position_t new_pos);

    // Saca un item del inventario segun 'type' y lo tira al mundo
    void dropItemFromInventoryToWorld(const int type);

    // Saca un item del inventario segun 'type' y lo devuelve
    Item* takeItemFromInventory(const int type);

    // Agrega un item al inventario
    void addItemToInventory(Item* item);

    // Agrega la cantidad recibida al oro al player
    void addGold(const int quant);

    // Devuelve el espacio para guardar oro de forma segura
    const int getSafeGoldSpace();

    // Remueve el oro en exceso del player
    const int removeExcessGold();

    // Saca un oro del mundo segun su pos (x,y) y guarda su cantidad
    void takeGoldFromWorld(position_t new_pos);

    // Compra un item
    void buyItem(Item* item);

    // Vende un item segun 'type'
    Item* sellItem(const int type);

    // Devuelve true si esta reviviendo, false en caso contrario
    const bool isWaitingToRevive() const;

    // Devuelve la experiencia actual en el nivel actual
    const long levelActualExperience() const;

    // Devuelve la experiencia maxima en el nivel actual
    const long levelMaxExperience() const;

    // Devuelve los segundos faltantes para revivir (aprox)
    const int secondsToRevive();

    // Devuelve el id del player
    const int getId() const;

    // Devuelve la posicion del player
    position_t getPos() const;
};

#endif // GAME_PLAYER_H
