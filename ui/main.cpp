#include "GUIWindow.h"
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
	Gtk::Main   kit( argc, argv );          
	GUIWindow window;
	Gtk::Main::run( window );
}
