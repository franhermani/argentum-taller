#include <gtkmm.h>

#define OK 0
#define ERROR 1

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("basic.glade");

    return OK;
}
