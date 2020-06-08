#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include "file.h"
#include "json.hpp"

using json = nlohmann::json;

class FileParser {
    File& file;

public:
    // Constructor
    explicit FileParser(File& file);

    // Obtiene el puerto del archivo
    const std::string getPort();

    // Obtiene los parametros del juego en formato json
    const json getGameParams();
};

#endif // FILE_PARSER_H
