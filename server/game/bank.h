#ifndef BANK_H
#define BANK_H

class Bank {
public:
    // Constructor
    Bank();

    // Constructor y asignacion por copia deshabilitados
    Bank(const Bank& other) = delete;
    Bank& operator=(const Bank& other) = delete;
};

#endif // BANK_H
