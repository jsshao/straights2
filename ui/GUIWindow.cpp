#include "GUIWindow.h"
#include <iostream>
using namespace std;

GUIWindow::GUIWindow() :
    table(4,13,true), start_("Start Game"), end_("End Game")
{
    table.set_row_spacings(10);
    table.set_col_spacings(10);
    set_border_width( 10 );
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i*13+j] = new Gtk::Image(card_manager.getCardImage((Faces)j, (Suits)i));
            table.attach(*cards[i*13+j], j, j+1, i, i+1);
        }
    }
	seed_.set_text("0");
    header.add(start_);
	header.add(seed_);
	header.add(end_);
    layout.add(header);
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
