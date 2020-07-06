#ifndef LIVING_BEING_H
#define LIVING_BEING_H

class Player;
class Creature;

class LivingBeing {
protected:
    int id{};
    int posX{}, posY{};
    int level{};
    bool isAlive{};
    int orientation{};
    int maxLife{};
    int actualLife{};

    friend class World;
    friend class Equations;

    // Resta puntos de vida
    void subtractLife(int life);

    // Muere
    // Metodo a definir por las clases derivadas
    virtual void die() = 0;

public:
    // Destructor
    virtual ~LivingBeing();

    // Actualiza segun 'ms'
    // Metodo a definir por las clases derivadas
    virtual void update(int ms) = 0;

    // Ataca a un player
    // Metodo a definir por las clases derivadas
    virtual void attack(Player& player) = 0;

    // Ataca a una criatura
    // Metodo a definir por las clases derivadas
    virtual void attack(Creature& creature) = 0;

    // Recibe un ataque y devuelve la cantidad de daño realmente recibido
    // Metodo a definir por las clases derivadas
    virtual const int receiveAttack(const int damage) = 0;

    // Devuelve true si esta muerto, false en caso contrario
    const bool isDead() const;
};

#endif // LIVING_BEING_H
