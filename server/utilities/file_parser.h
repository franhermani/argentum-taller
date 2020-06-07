#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include "file.h"

class FileParser {
    File& file;

public:
    // Constructor
    explicit FileParser(File& file);

    // Obtiene el puerto del archivo
    const std::string getPort();
};

#endif // FILE_PARSER_H
