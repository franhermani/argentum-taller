#ifndef ITEM_H
#define ITEM_H

class Item {
public:
    // Destructor
    virtual ~Item();

    // Equipa el item en cuestion
    // Metodo a definir por las clases derivadas
    virtual void equip() = 0;
};

#endif // ITEM_H
