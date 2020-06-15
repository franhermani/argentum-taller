#include "params.h"

GameParams::GameParams(const json& config_params, const json& world_params) :
configParams(config_params), worldParams(world_params) {}

const json GameParams::getConfigParams() const {
    return configParams;
}

const json GameParams::getWorldParams() const {
    return worldParams;
}
