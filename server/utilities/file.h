#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

class File {
    std::ifstream ifs;
    std::string path;
    bool isOpen;

public:
    // Constructor
    explicit File(std::string path);

    // Constructor y asignacion por copia deshabilitados
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    
    // Destructor
    // Cierra el archivo si sigue abierto
    ~File();

    // Abre el archivo
    void openFD();

    // Cierra el archivo
    void closeFD();

    // Devuelve una referencia al archivo
    std::ifstream& getFile();
};

#endif // FILE_H
