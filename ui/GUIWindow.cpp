#include <gtkmm/messagedialog.h>
#include <gtkmm/dialog.h>
#include <gtkmm/stock.h>
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

    for (int i = 0; i < 4; i++) {
        std::ostringstream oss;
        oss << (i+1);

        playerFrame[i].set_label("Player " + oss.str());
        switchButton[i].set_label("Rage");
        points[i].set_text("0 points");
        discards[i].set_text("0 discards");
        player[i].add(switchButton[i]);
        player[i].add(points[i]);
        player[i].add(discards[i]);
        playerFrame[i].add(player[i]);
        players.add(playerFrame[i]);
    }
    seed_.set_text("0");
    header.add(start_);
    header.add(seed_);
    header.add(end_);
    layout.set_spacing(10);
    layout.add(header);
    tableFrame.set_label("Cards on the table");
    tableFrame.add(table);
    layout.add(tableFrame);
    layout.add(players);

    handFrame_.set_label("Your hand");
    for (int i = 0; i < 13; i++) {
        hand_cards[i] = new Gtk::Image(card_manager.getCardImage((Faces)i, (Suits)0));
        handButtons_[i].add(*hand_cards[i]);
        hand_.add(handButtons_[i]);
    }
    handFrame_.add(hand_);
    layout.add(handFrame_);

	Gtk::MessageDialog dialogue(*this, "BOOGA");
	dialogue.run();
	add(layout);

    show_all();
}

GUIWindow::~GUIWindow() {
    for (int i = 0; i < 52; i++) {
        delete cards[i];
    }
    for (int i = 0; i < 13; i++) {
        delete hand_cards[i];
    }

}
