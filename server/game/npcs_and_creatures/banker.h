#ifndef BANKER_H
#define BANKER_H

#include <vector>
#include "npc.h"
#include "../player.h"

class Banker : public NPC {
public:
    // Constructor
    Banker(const int pos_x, const int pos_y, const int orient);

    // Constructor y asignacion por copia deshabilitados
    Banker(const Banker& other) = delete;
    Banker& operator=(const Banker& other) = delete;

    // Destructor
    ~Banker();

    // Deposita el item del player en el banco
    void depositItem(Player& player, int item_type);

    // Retira el item del player del banco
    void withdrawItem(Player& player, int item_type);

    // Deposita la cantidad recibida de oro del player en el banco
    void depositGold(Player& player, int quantity);

    // Retira la cantidad recibida de oro del player del banco
    void withdrawGold(Player& player, int quantity);

    // Lista los items que tiene el player en el banco
    // TODO: necesita recibir al player por parametro
    const std::vector<itemType> listItems() const override;
};

#endif // BANKER_H
