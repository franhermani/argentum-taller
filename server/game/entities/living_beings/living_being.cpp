#include "living_being.h"

LivingBeing::~LivingBeing() = default;

void LivingBeing::subtractLife(int life) {
    actualLife -= life;

    if (actualLife < 0)
        actualLife = 0;

    if (actualLife == 0)
        die();
}

const bool LivingBeing::isDead() const {
    return (! isAlive);
}
