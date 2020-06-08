#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

class Protocol {
protected:
    // Codifica un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual void encodeMessage() = 0;

    // Decodifica un mensaje segun el protocolo
    // Metodo a definir por las clases derivadas
    virtual void decodeMessage() = 0;

public:
    // Recibe un mensaje a traves del socket
    // Metodo a definir por las clases derivadas
    virtual const std::string receiveMessage() = 0;

    // Envia un mensaje a traves del socket
    // Metodo a definir por las clases derivadas
    virtual void sendMessage(const std::string& message) = 0;
};

#endif // PROTOCOL_H
