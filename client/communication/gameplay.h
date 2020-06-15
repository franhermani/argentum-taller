
#ifndef ARGENTUM_GAMEPLAY_H
#define ARGENTUM_GAMEPLAY_H
#include <SDL2/SDL.h>
#include "../../common/thread.h"


class Gameplay : public Thread {
public:

    // Constructor
    Gameplay();

    // Destructor
    ~Gameplay();

    // Constructor y asignacion por copia deshabilitados
    Gameplay(const Gameplay &) = delete;
    Gameplay &operator=(const Gameplay &) = delete;

    //ciclo de interaccion con teclado
    void play();

    // Inicializa los thread sender y receiver
    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;
};


#endif //ARGENTUM_GAMEPLAY_H
