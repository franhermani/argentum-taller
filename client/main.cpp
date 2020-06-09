#include <gtkmm.h>
#include <iostream>
#include "communication/client.h"
#include "../common/socket_error.h"
#include "../server/defines.h"

#define OK 0
#define ERROR 1
#define NUM_PARAMS 1

int main(int argc, char *argv[]) {
    if (argc != NUM_PARAMS) {
        std::cerr << "Uso: ./client\n";
        return ERROR;
    }
    // TODO: esto se lee de una pantalla de login
    const char *host = "localhost", *port = "8080";

    try {
        Client client(host, port);
        client.connectToServer();
//        client.disconnectFromServer();
//        client.play();
        // TODO: este loop en realidad no va, pero si lo saco se cuelga
        std::string command;
        while (getline(std::cin, command))
            if (command == EXIT_CHAR) break;
    } catch(SocketError& e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Error desconocido\n";
    }
    return OK;
}

/*
int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    Gtk::Dialog* pDialog;

    // Cargo el GtkBuilder file e instancio sus widgets
    auto refBuilder = Gtk::Builder::create();

    try {
        // TODO: no encuentra el archivo
        refBuilder->add_from_file("basic.glade");
    } catch(const Glib::FileError& e) {
        std::cerr << "FileError: " << e.what() << std::endl;
        return ERROR;
    } catch(const Glib::MarkupError& e) {
        std::cerr << "MarkupError: " << e.what() << std::endl;
        return ERROR;
    } catch(const Gtk::BuilderError& e) {
        std::cerr << "BuilderError: " << e.what() << std::endl;
        return ERROR;
    }

    // Obtengo el GtkBuilder widget
    refBuilder->get_widget("DialogBasic", pDialog);

    // Ejecuto el dialogo
    if(pDialog) app->run(*pDialog);

    // Elimino el dialogo
    delete pDialog;

    return OK;
}
*/
