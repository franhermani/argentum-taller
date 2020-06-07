#ifndef FILE_H
#define FILE_H

#include <fstream>

class File {
    std::ifstream ifs;
    bool isOpen;

public:
    // Constructor
    // Abre el archivo
    explicit File(const char *path);

    // Constructor y asignacion por copia deshabilitados
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    
    // Destructor
    // Cierra el archivo si no se pudo cerrar antes
    ~File();

    // Cierra el archivo
    void closeFD();

    // Devuelve una referencia al archivo
    std::ifstream& getFile();
};

#endif // FILE_H
