#include <fstream>
#include <exception>
#include "file.h"

File::File(const char *path) {
    ifs.open(path, std::ifstream::in);
    if (! ifs.good()) throw std::runtime_error("Error al abrir el archivo\n");
    isOpen = true;
}

File::~File() {
    if (isOpen) closeFD();
}

void File::closeFD() {
    ifs.close();
    isOpen = false;
}

std::ifstream& File::getFile() {
    return ifs;
}
