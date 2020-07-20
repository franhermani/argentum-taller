#ifndef ATTACKS_H
#define ATTACKS_H

#define MELEE_STRING                    "melee"
#define MAGIC_ARROW_SPELL_STRING        "magic_arrow_spell"
#define HEAL_SPELL_STRING               "heal_spell"
#define MISSILE_SPELL_STRING            "missile_spell"
#define EXPLOSION_SPELL_STRING          "explosion_spell"
#define SINGLE_ARROW_STRING             "single_arrow"
#define MULTIPLE_ARROW_STRING           "multiple_arrow"

enum attackType {
    MELEE,
    NO_WEAPON_MELEE,
    MAGIC_ARROW_SPELL,
    HEAL_SPELL,
    MISSILE_SPELL,
    EXPLOSION_SPELL,
    SINGLE_ARROW,
    MULTIPLE_ARROW
};

enum soundType {
    PLAYER_PUNCH,
    CREATURE_PUNCH,
    SWORD_STRIKE,
    AXE_STRIKE,
    HAMMER_STRIKE,
    ARROW_STRIKE,
    MAGIC_STRIKE,
    HEAL_STRIKE,
    EXPLOSION
};

#endif // ATTACKS_H
