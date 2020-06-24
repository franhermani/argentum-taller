#include "armor.h"

Armor::Armor(const int type, const int min_defense, const int max_defense) :
type(type), minDefense(min_defense), maxDefense(max_defense) {}

Armor::~Armor() = default;
