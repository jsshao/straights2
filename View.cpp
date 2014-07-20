#include "View.h"
#include <iostream>
#include <cstdlib>
using namespace std;

View::View(Controller *c, Model *m) :
    controller_(c), model_(m), table(4,13,true), start_("Start Game"), end_("End Game")
{
    const Glib::RefPtr<Gdk::Pixbuf> null = card_manager.getNull();
    table.set_row_spacings(10);
    table.set_col_spacings(10);
    set_border_width( 10 );
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i*13+j] = new Gtk::Image(null);
            table.attach(*cards[i*13+j], j, j+1, i, i+1);
        }
    }

    for (int i = 0; i < 4; i++) {
        std::ostringstream oss;
        oss << (i+1);

        playerFrame[i].set_label("Player " + oss.str());
        switchButton[i].set_label("Human");
        switchButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &View::switchClicked), i));
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
        hand_cards[i] = new Gtk::Image(null);
        handButtons_[i].add(*hand_cards[i]);
        handButtons_[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun( *this, &View::cardClicked), i) );
        hand_.add(handButtons_[i]);
    }
    handFrame_.add(hand_);
    layout.add(handFrame_);
    add(layout);
	start_.signal_clicked().connect( sigc::mem_fun( *this, &View::startClicked ) );
	end_.signal_clicked().connect( sigc::mem_fun( *this, &View::endClicked ) );

    show_all();
    model_->subscribe(this);
}

View::~View() {
    for (int i = 0; i < 52; i++) {
        delete cards[i];
    }
    for (int i = 0; i < 13; i++) {
        delete hand_cards[i];
    }

}

void View::update() {
    const Glib::RefPtr<Gdk::Pixbuf> null = card_manager.getNull();
    for (int i = 0; i < 4; i++) {
        if (!model_->gameStarted()) {
            switchButton[i].set_label(model_->isPlayerComputer(i+1)?"Computer":"Human");
            switchButton[i].set_sensitive(true);
        } else {
            switchButton[i].set_label("Rage");
            switchButton[i].set_sensitive(model_->currentPlayer() == i+1);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i*13+j]->set(null);
        }
    }    
    for (size_t i = 0; i < 13; i++) {
        hand_cards[i]->set(null);
    }
    if (model_->gameStarted()) {
        vector<Card> table = model_->getTable();
        for (size_t i = 0; i < table.size(); i++) {
            cards[(int)table[i].getSuit()*13 + (int)table[i].getRank()]->set(card_manager.getCard(table[i].getRank(), table[i].getSuit()));
        }
        vector<Card> hand = model_->getCurHand();
        for (size_t i = 0; i < hand.size(); i++) {
            hand_cards[i]->set(card_manager.getCard(hand[i].getRank(), hand[i].getSuit())); 
        }
    }

	vector<int> scores = model_->getScores();
	for (int i = 0; i < scores.size(); i++) {
		std::ostringstream oss;
		oss << scores[i];
		points[i].set_text(oss.str()+" points");
	}	
}

void View::startClicked() {
    cout << "start clicked" << endl;
    cout << "seed is " << atoi(seed_.get_text().c_str()) << endl;
    controller_->setSeed(atoi(seed_.get_text().c_str()));
    controller_->startGame();
}

void View::endClicked() {
    cout << "end clicked" << endl;
    controller_->endGame();
}

void View::cardClicked(int which) {
    cout << "card " << which << " clicked" << endl;
    controller_->selectCard(which);
}

void View::switchClicked(int which) {
    cout << "switch " << which << " clicked" << endl;
    controller_->togglePlayerType(which+1);
}
