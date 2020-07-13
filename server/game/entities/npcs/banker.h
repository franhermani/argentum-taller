#ifndef BANKER_H
#define BANKER_H

#include <vector>
#include "npc.h"
#include "../living_beings/player.h"
#include "../../bank.h"

class Banker : public NPC {
    Bank& bank;

public:
    // Constructor
    Banker(Bank& bank, position_t new_pos);

    // Constructor y asignacion por copia deshabilitados
    Banker(const Banker& other) = delete;
    Banker& operator=(const Banker& other) = delete;

    // Destructor
    ~Banker();

    // Lanza una excepcion
    void revive(Player& player) override;

    // Lanza una excepcion
    void heal(Player& player) override;

    // Lanza una excepcion
    void buyItem(Player& player, const int type) override;

    // Lanza una excepcion
    void sellItem(Player& player, const int type) override;

    // Deposita el item del player en el banco
    void depositItem(Player& player, const int type) override;

    // Retira el item del player del banco
    void withdrawItem(Player& player, const int type) override;

    // Deposita el oro en exceso del player en el banco
    void depositGold(Player& player) override;

    // Retira oro del player del banco
    // Retira el maximo entre el oro en el banco y el oro seguro disponible
    void withdrawGold(Player& player) override;

    // Lista los items y la cantidad de oro que tiene el player en el banco
    list_t listItems(Player& player) const override;
};

#endif // BANKER_H
