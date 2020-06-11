#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include "file.h"
#include "json.hpp"

using json = nlohmann::json;

class JsonParser {
    json j;

public:
    // Constructor
    // Guarda el contenido del json file en 'j'
    explicit JsonParser(File& file);

    // Obtiene el puerto del archivo
    const std::string getPort();

    // Obtiene los parametros del juego en formato json
    const json getGameParams();

    // Obtiene el mapa generado por Tiled en formato json
    const json getWorldParams();
};

#endif // FILE_PARSER_H
