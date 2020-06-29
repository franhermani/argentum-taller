#ifndef NPC_H
#define NPC_H

class NPC {
protected:
    int posX, posY;
    int orientation;

    friend class World;

public:
    // Destructor
    virtual ~NPC();
};

#endif // NPC_H
