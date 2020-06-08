#include "params.h"

GameParams::GameParams(const json &json_params) : jsonParams(json_params),
worldWidth(json_params["world_width"]),
worldHeight(json_params["world_height"]) {}
