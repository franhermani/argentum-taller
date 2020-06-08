#include <string>
#include "file_parser.h"
#include "json.hpp"

FileParser::FileParser(File& file) : file(file) {}

const std::string FileParser::getPort() {
    json j;
    file.openFD();
    file.getFile() >> j;
    file.closeFD();

    return j["communication"]["port"].get<std::string>();
}

const json FileParser::getGameParams() {
    json j;
    file.openFD();
    file.getFile() >> j;
    file.closeFD();

    return j["game_params"];
}
