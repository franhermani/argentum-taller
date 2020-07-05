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
    Banker(Bank& bank, const int pos_x, const int pos_y,
            const int orient);

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

    // Deposita la cantidad recibida de oro del player en el banco
    void depositGold(Player& player, const int quant) override;

    // Retira la cantidad recibida de oro del player del banco
    void withdrawGold(Player& player, const int quant) override;

    // Lista los items que tiene el player en el banco
    // TODO: necesita recibir al player por parametro
    const std::vector<int> listItems() const override;
};

#endif // BANKER_H
