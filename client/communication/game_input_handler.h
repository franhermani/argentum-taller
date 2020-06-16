
#ifndef ARGENTUM_GAME_INPUT_HANDLER_H
#define ARGENTUM_GAME_INPUT_HANDLER_H
#include <SDL2/SDL.h>
#include "../../common/thread.h"
#include "../../common/blocking_queue.h"
#include "../../common/commands/command.h"
#include "../../common/commands/move_command.h"
#include "../../common/commands/defines.h"


class GameInputHandler : public Thread {
public:
    BlockingQueue<Command*>& commandQueue;

    // Constructor
    GameInputHandler(BlockingQueue<Command*>& commandQueue);

    // Destructor
    ~GameInputHandler();

    // Constructor y asignacion por copia deshabilitados
    GameInputHandler(const GameInputHandler &) = delete;
    GameInputHandler &operator=(const GameInputHandler &) = delete;

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


#endif //ARGENTUM_GAME_INPUT_HANDLER_H
