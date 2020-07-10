#ifndef NPC_H
#define NPC_H

#include <vector>
#include "../../../../common/defines/items.h"
#include "../../../../common/defines/world_structs.h"
#include "../../../../common/defines/position.h"

class Player;

class NPC {
protected:
    int type;
    position_t pos;
    int orientation;
    std::vector<int> items;

    friend class World;
    friend class ServerProtocol;

public:
    // Destructor
    virtual ~NPC();

    // Revive al player
    // Metodo a definir por las clases derivadas
    virtual void revive(Player& player) = 0;

    // Cura al player
    // Metodo a definir por las clases derivadas
    virtual void heal(Player& player) = 0;

    // Compra un item al player segun 'item_type'
    // Metodo a definir por las clases derivadas
    virtual void buyItem(Player& player, const int type) = 0;

    // Vende un item al player segun 'item_type'
    // Metodo a definir por las clases derivadas
    virtual void sellItem(Player& player, const int type) = 0;

    // Deposita el item del player en el banco
    // Metodo a definir por las clases derivadas
    virtual void depositItem(Player& player, const int type) = 0;

    // Retira el item del player del banco
    // Metodo a definir por las clases derivadas
    virtual void withdrawItem(Player& player, const int type) = 0;

    // Deposita la cantidad recibida de oro del player en el banco
    // Metodo a definir por las clases derivadas
    virtual void depositGold(Player& player, const int quant) = 0;

    // Retira la cantidad recibida de oro del player del banco
    // Metodo a definir por las clases derivadas
    virtual void withdrawGold(Player& player, const int quant) = 0;

    // Lista los items que tiene para ofrecer
    // Metodo a definir por las clases derivadas
    virtual list_t listItems(Player& player) const = 0;
};

#endif // NPC_H
