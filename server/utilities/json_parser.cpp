#include <string>
#include "json_parser.h"
#include "json.hpp"

JsonParser::JsonParser(File& file) {
    file.openFD();
    file.getFile() >> j;
    file.closeFD();
}

const std::string JsonParser::getPort() {
    return j["communication"]["port"].get<std::string>();
}

const json JsonParser::getGameParams() {
    return j["game_params"];
}

const json JsonParser::getWorldParams() {
    return j;
}
