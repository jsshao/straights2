#include "View.h"
#include <gtkmm/messagedialog.h>
#include <iostream>
#include <cstdlib>
using namespace std;

// Constructor to intialize the layout
View::View(Controller *c, Model *m) :
    controller_(c), model_(m), table(4,13,true), start_("Start Game"), end_("End Game")
{
	// Initialize empty table
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

	// Intialize players info to 0 points, 0 discards
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

	// Intialize seed
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

	// Intialize cards in hand to be empty
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

	// Display all
    show_all();
    model_->subscribe(this);
}

// Destructor that deletes cards that were dynamically allocated
View::~View() {
    for (int i = 0; i < 52; i++) {
        delete cards[i];
    }
    for (int i = 0; i < 13; i++) {
        delete hand_cards[i];
    }

}

// Reloads informationt and queries info from the Model like points, discards, hand, table
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
        handButtons_[i].set_sensitive(false);
    }
    if (model_->gameStarted()) {
        vector<Card> table = model_->getTable();
        for (size_t i = 0; i < table.size(); i++) {
            cards[(int)table[i].getSuit()*13 + (int)table[i].getRank()]->set(card_manager.getCard(table[i].getRank(), table[i].getSuit()));
        }
        vector<Card> hand = model_->getCurHand();
        vector<int> moves = model_->getMoves();
        for (size_t i = 0; i < hand.size(); i++) {
            hand_cards[i]->set(card_manager.getCard(hand[i].getRank(), hand[i].getSuit())); 
            if (!moves.size())
                handButtons_[i].set_sensitive(true);
        }
        for (size_t i = 0; i < moves.size(); i++) {
            handButtons_[moves[i]].set_sensitive(true);
        }
    } else {
		for (int i = 0; i < 4; i++) {
			points[i].set_text("0 points");
        	discards[i].set_text("0 discards");
		}
	
		for (size_t i = 0; i < 13; i++) {
       		hand_cards[i]->set(null);
        	handButtons_[i].set_sensitive(false);
    	}
	}

	if (model_->gameStarted()) {
		vector<int> scores = model_->getScores();
		vector<vector<Card> > Discards = model_->getDiscards();
		for (size_t i = 0; i < scores.size(); i++) {
			std::ostringstream oss, oss2;
			oss << scores[i];
			points[i].set_text(oss.str()+" points");
			oss2 << Discards[i].size();
			discards[i].set_text(oss2.str()+" discards");
		}	
	}

	if (model_->getMessage() != "") {
		Gtk::MessageDialog dialogue(*this, model_->getMessage());
    	dialogue.run();
	}
}

// Set the seed
void View::startClicked() {
    controller_->setSeed(atoi(seed_.get_text().c_str()));
    controller_->startGame();
}

// End the game
void View::endClicked() {
    controller_->endGame();
}

// Play the clicked card
void View::cardClicked(int which) {
    controller_->selectCard(which);
}

// Switch that player between AI/Human
void View::switchClicked(int which) {
    controller_->togglePlayerType(which+1);
}
