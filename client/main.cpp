#include <gtkmm.h>
#include <iostream>

#define OK 0
#define ERROR 1

int main(int argc, char *argv[]) {
    return OK;
}

/*
int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    Gtk::Dialog* pDialog;

    // Cargo el GtkBuilder file e instancio sus widgets
    auto refBuilder = Gtk::Builder::create();

    try {
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
