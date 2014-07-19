#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/table.h>
#include <vector>
#include "GUIWindow.h"
#include <iostream>
using namespace std;

GUIWindow::GUIWindow() :
    table(10,10,true)
{
    set_border_width( 10 );

    cards = new Gtk::Image** [4];
    for (int i = 0; i < 4; i++) {
        cards[i] = new Gtk::Image* [13];
        for (int j = 0; j < 13; j++) {
            cards[j][i] = new Gtk::Image(card_manager.getCardImage((Faces)j, (Suits)i));
            table.attach(*cards[j][i], j, j+1, i, i+1);
        }
    }
    layout.add(table);
    add(layout);

    show_all();
}

GUIWindow::~GUIWindow() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            delete cards[j][i];
        }
    }
    
}
