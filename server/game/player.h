#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "items/inventory.h"

class World;
class Equations;
class ClientHandler;
class ServerProtocol;

class Player {
    World& world;
    Equations& equations;
    int id;
    int raceType;
    int classType;
    int posX{}, posY{};
    int level;
    long maxExperience;
    long actualExperience;
    bool isAlive;
    bool isMeditating;
    int orientation;
    int armor;              // TODO: crear enum
    int helmet;             // TODO: crear enum
    int shield;             // TODO: crear enum
    int weapon;             // TODO: crear enum
    int maxLife;
    int actualLife;
    int maxMana;
    int actualMana;
    int maxGold;
    int actualGold;
    Inventory* inventory;

    // Genera posiciones iniciales aleatorias para el player
    void loadInitialPosition();

    // Resta puntos de vida al player
    void subtractLife(int life);

    // Suma puntos de vida al player
    void addLife(int life);

    // Suma puntos de mana al player
    void addMana(int mana);

    // Suma puntos de experiencia al player
    // Si llega al limite, sube de nivel
    void addExperience(int exp);

    // Setea 'isAlive' en false
    void die();

    friend class World;
    friend class Equations;
    friend class ClientHandler;
    friend class ServerProtocol;

public:
    // Constructor
    Player(World& world, Equations& equations, const int id,
            const int race_type, const int class_type);

    // Constructor y asignacion por copia deshabilitados
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    // Destructor
    // Libera la memoria reservada para el inventario
    ~Player();

    // Recupera vida y mana con el paso del tiempo
    // Recupera mana con el estado de meditacion
    void update(int ms);

    // Mueve el player segun la direccion dada
    void moveTo(int direction);

    // Recupera todos los puntos de vida y mana del player
    void heal();

    // Revive al player
    void revive();

    // El player entra en estado de meditacion
    void meditate();

    // Ataca a otro player o NPC segun su ID
    void attack(const int enemy_id_type, const int enemy_id);

    // Recibe el ataque de otro player o NPC
    // Devuelve la cantidad de daño realmente recibido
    const int receiveAttack(const int damage);

    // Agrega un item al inventario
    void addItemToInventory(Item* item);

    // Saca un item del inventario segun su posicion
    Item* removeItemFromInventory(const int pos);

    // TODO: ver si recibir int o Item
    // Asigna el enumType a 'armor'
    void equipArmor(const int type);

    // Asigna el enumType a 'helmet'
    void equipHelmet(const int type);

    // Asigna el enumType a 'shield'
    void equipShield(const int type);

    // Asigna el enumType a 'weapon'
    void equipWeapon(const int type);
};

#endif // GAME_PLAYER_H
