#include <string>
#include "json_parser.h"
#include "json.hpp"

JsonParser::JsonParser() {}

const json JsonParser::fileToJson(File &file) {
    json j;
    file.openFD();
    file.getFile() >> j;
    file.closeFD();
    return j;
}

const std::string JsonParser::getPort(File &file) {
    json j = fileToJson(file);
    return j["communication"]["port"].get<std::string>();
}

const json JsonParser::getConfigParams(File &file) {
    json j = fileToJson(file);
    return j["game_params"];
}

const json JsonParser::getWorldParams(File &file) {
    json j = fileToJson(file);
    return j;
}

const json JsonParser::getResolution(File &file) {
    json j = fileToJson(file);
    return j["resolution"];
}
