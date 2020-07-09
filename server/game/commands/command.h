#ifndef COMMAND_H
#define COMMAND_H

class World;

class Command {
public:
    // Destructor
    virtual ~Command();

    // Ejecuta el comando
    // Metodo a definir por las clases derivadas
    virtual void execute(World& world) = 0;
};

#endif // COMMAND_H
