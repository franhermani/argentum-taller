#include "helmet.h"

Helmet::Helmet(const int type, const int min_defense, const int max_defense,
        const bool is_magic) : type(type), minDefense(min_defense),
        maxDefense(max_defense), isMagic(is_magic) {}

Helmet::~Helmet() = default;
