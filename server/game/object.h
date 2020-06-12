#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
protected:
    int id;
    int posX, posY;
    bool isImpenetrable;

    friend class World;
public:
    // Ejecuta las acciones basadas en el tiempo
    // Metodo a definir por las clases derivadas
    virtual void update(int ms) = 0;
};

#endif // GAME_OBJECT_H
