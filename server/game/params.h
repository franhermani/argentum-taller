#ifndef GAME_PARAMS_H
#define GAME_PARAMS_H

#include "../../common/utilities/json_parser.h"
#include "../../common/utilities/json.hpp"

using json = nlohmann::json;

class GameParams {
    json configParams;
    json worldParams;

public:
    // Constructor
    GameParams(const json& config_params, const json& world_params);

    // Constructor y asignacion por copia deshabilitados
    GameParams(const GameParams& other) = delete;
    GameParams& operator=(const GameParams& other) = delete;

    // Devuelve los parametros de configuracion del juego en formato Json
    const json getConfigParams() const;

    // Devuelve los parametros del mapa del juego en formato Json
    const json getWorldParams() const;
};

#endif // GAME_PARAMS_H
