#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

enum exceptionCode {
    // Un guerrero intenta meditar
    UNABLE_TO_MEDITATE,

    // Un guerrero intenta equiparse un item magico
    UNABLE_TO_USE_MAGIC,

    // Un player esta muerto e intenta interactura con un item u otro player
    UNABLE_TO_INTERACT,

    // Un player esta vivo e intenta revivir
    UNABLE_TO_REVIVE,

    // Un player intenta atacar en una zona segura
    UNABLE_TO_ATTACK_IN_SAFE_ZONE,

    // Un player intenta atacar a otro player muerto
    UNABLE_TO_ATTACK_DEAD_PLAYER,

    // Un player newbie no puede atacar ni ser atacado por otro player
    NEWBIE_ATTACK_FORBIDDEN,

    // Un player no puede atacar a otro si la diferencia de niveles
    // entre ellos es alta
    DIFF_LEVEL_ATTACK_FORBIDDEN,

    // Un player no tiene suficiente oro para comprar un item
    INSUFFICIENT_GOLD,

    // Un player intenta agregar un ítem al inventario y ya esta lleno
    FULL_INVENTORY,

    // Un player intenta agregar un item de caracter unico al inventario
    // y ya existe
    ITEM_ALREADY_IN_INVENTORY,

    // Un player intenta tirar un item en una posicion
    // en la que ya hay otro item
    ITEM_IN_POSITION
};

#endif // GAME_EXCEPTIONS_H
