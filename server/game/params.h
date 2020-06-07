#ifndef GAME_PARAMS_H
#define GAME_PARAMS_H

#include "../utilities/file_parser.h"
#include "../utilities/json.hpp"

using json = nlohmann::json;

class GameParams {
    json jsonParams;
    int worldWidth;
    int worldHeight;

public:
    // Constructor
    explicit GameParams(const json& json_params);

    // Constructor y asignacion por copia deshabilitados
    GameParams(const GameParams& other) = delete;
    GameParams& operator=(const GameParams& other) = delete;
};

#endif // GAME_PARAMS_H
