#include <fstream>
#include <string>
#include <utility>
#include "file.h"

File::File(std::string path) : path(std::move(path)), isOpen(false) {}

File::~File() {
    if (isOpen) closeFD();
}

void File::openFD() {
    if (isOpen) return;
    ifs.open(path, std::ifstream::in);
    if (! ifs.good()) throw std::runtime_error(
            std::string("Error al abrir el archivo ") + path + "\n");
    isOpen = true;
}

void File::closeFD() {
    if (! isOpen) return;
    ifs.close();
    isOpen = false;
}

std::ifstream& File::getFile() {
    return ifs;
}
