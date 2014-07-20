#include <cstdio>
#include <cstdlib>
#include "Game.h"
#include "gtkmm/main.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

// Main class to start up the game of Straights 
int main(int argc, char* argv[]) {
    // Initialize seed as 0 originally 
    srand48(0);

	Gtk::Main  kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
    Model model;                          // Create model
    Controller controller( &model );      // Create controller
    View view( &controller, &model );     // Create the view -- is passed handle to controller and model
    Gtk::Main::run( view );               // Show the window and return when it is closed.

    return 0;
}
