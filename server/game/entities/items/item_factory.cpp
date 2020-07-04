#include "item_factory.h"

ItemFactory::ItemFactory() = default;

Item* ItemFactory::operator()(const int type, const int pos_x,
        const int pos_y) {
    // TODO: ver como hacerle llegar los params del json
}