#include <string>
#include <utility>
#include "file_parser.h"
#include "../utilities/json.hpp"
#include "../defines.h"

using json = nlohmann::json;

FileParser::FileParser(File& file) : file(file) {}

const std::string FileParser::getPort() {
    json j;
    file.openFD();
    file.getFile() >> j;
    std::string port = j[PORT].get<std::string>();
    file.closeFD();

    return std::move(port);
}
