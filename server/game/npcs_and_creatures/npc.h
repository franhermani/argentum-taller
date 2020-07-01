#ifndef NPC_H
#define NPC_H

#include <vector>
#include "../../../common/defines/items.h"

class NPC {
protected:
    int type;
    int posX, posY;
    int orientation;
    std::vector<itemType> items;

    friend class World;
    friend class ServerProtocol;

public:
    // Destructor
    virtual ~NPC();

    // Lista los items que tiene para ofrecer
    // Metodo a definir por las clases derivadas
    virtual const std::vector<itemType> listItems() const = 0;
};

#endif // NPC_H
