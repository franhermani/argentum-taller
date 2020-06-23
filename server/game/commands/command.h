#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    // Destructor
    virtual ~Command();

    // Ejecuta el comando
    // Metodo a definir por las clases derivadas
    virtual void execute() = 0;
};

#endif // COMMAND_H
