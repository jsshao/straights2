#include "GUIWindow.h"
#include <iostream>
using namespace std;

GUIWindow::GUIWindow() :
    table(10,10,true)
{
    set_border_width( 10 );
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i*13+j] = new Gtk::Image(card_manager.getCardImage((Faces)j, (Suits)i));
            table.attach(*cards[i*13+j], j, j+1, i, i+1);
        }
    }
    layout.add(table);
    add(layout);

    show_all();
}

GUIWindow::~GUIWindow() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            delete cards[i*13+j];
        }
    }
    
}
