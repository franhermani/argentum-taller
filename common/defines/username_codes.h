#ifndef USERNAME_CONFIRMATION_H
#define USERNAME_CONFIRMATION_H

struct NoMoreAvailableIdsException : public std::exception {
    const char* what() const throw() {
        return "Límite de usuarios alcanzado\n";
    }
};

struct DuplicatedUsernameException : public std::exception {
    const char* what() const throw() {
        return "Nombre de usuario no disponible\n";
    }
};

enum usernameCode {
    USERNAME_OK,
    USERNAME_DUPLICATED,
    NO_MORE_USERNAME_IDS
};

#endif // USERNAME_CONFIRMATION_H
