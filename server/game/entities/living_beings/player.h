#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "living_being.h"
#include "../items/weapon.h"
#include "../items/armor.h"
#include "../items/helmet.h"
#include "../items/shield.h"
#include "../items/potion.h"
#include "../items/inventory.h"
#include "creature.h"

class World;
class Equations;
class ClientHandler;
class ServerProtocol;

class Player : public LivingBeing {
    World& world;
    Equations& equations;
    int raceType;
    int classType;
    long maxExperience;
    long actualExperience;
    bool isMeditating;
    bool isNewbie;
    bool ableToUseMagic;
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
    int recoveryVelocity;

    // Genera posiciones iniciales aleatorias para el player
    void loadInitialPosition();

    // Suma puntos de vida al player
    void addLife(int life);

    // Resta puntos de mana al player
    void subtractMana(int mana);

    // Suma puntos de mana al player
    void addMana(int mana);

    // Suma puntos de experiencia al player
    // Si llega al limite, sube de nivel
    void addExperience(int exp);

    // Setea 'isAlive' en false y dropea oro e items del inventario
    virtual void die() override;

    // Dropea el oro en exceso al mundo
    void dropExcessGold();

    // Dropea los items del inventario al mundo
    void dropInventoryItems();

    // Setea 'isMeditating' en false
    void stopMeditating();

    // Asigna 'new_weapon' a 'weapon'
    // Lanza una excepcion si:
    // - el arma es magica y player no puede usar la magia
    void equipWeapon(Weapon* new_weapon);

    // Asigna 'new_armor' a 'armor'
    void equipArmor(Armor* new_armor);

    // Asigna 'new_helmet' a 'helmet'
    // Lanza una excepcion si:
    // - el arma es magica y player no puede usar la magia
    void equipHelmet(Helmet* new_helmet);

    // Asigna el 'new_shield' a 'shield'
    void equipShield(Shield* new_shield);

    // Suma los puntos de vida y mana correspondientes segun la pocion
    void equipPotion(Potion* new_potion);

    friend class World;
    friend class Equations;
    friend class Banker;
    friend class ClientHandler;
    friend class ServerProtocol;

public:
    // Constructor
    Player(World& world, Equations& equations, const int new_id,
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

    // Revive al player
    void revive();

    // El player entra en estado de meditacion
    // Lanza una excepcion si:
    // - el player no puede usar la magia
    void meditate();

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

    // Saca un item del mundo segun su pos (x,y) y lo guarda en el inventario
    void takeItemFromWorldToInventory(const int pos_x, const int pos_y);

    // Saca un item del inventario segun 'type' y lo tira al mundo
    void dropItemFromInventoryToWorld(const int type);

    // Saca un item del inventario segun 'type' y lo devuelve
    Item* takeItemFromInventory(const int type);

    // Agrega un item al inventario
    void addItemToInventory(Item* item);

    // Agrega 'quant' oro al player
    void addGold(const int quant);

    // Remueve 'quant' oro del player
    void removeGold(const int quant);

    // Saca un oro del mundo segun su pos (x,y) y guarda su cantidad
    void takeGoldFromWorld(const int pos_x, const int pos_y);
};

#endif // GAME_PLAYER_H
