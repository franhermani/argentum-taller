#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include "file.h"
#include "json.hpp"

using json = nlohmann::json;

class JsonParser {
    // Convierte el archivo en formato Json a un json pp dicho
    const json fileToJson(File& file);

public:
    // Constructor
    JsonParser();

    // Obtiene el puerto del archivo
    const std::string getPort(File& file);

    // Obtiene los parametros del juego en formato json
    const json getConfigParams(File& file);

    // Obtiene el mapa generado por Tiled en formato json
    const json getWorldParams(File& file);
};

#endif // FILE_PARSER_H
