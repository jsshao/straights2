#ifndef VIEW_H
#define VIEW_H 

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <vector>
#include "DeckGUI.h"
#include "Controller.h"
#include "Model.h"

class View : public Gtk::Window, public Observer {
public:
	// Constructor
    View(Controller *c, Model *m);
    
	// Desctructor
	virtual ~View();

	// Update the view by quering info from the model
    virtual void update();

	// Behaviour when start game is clicked
    virtual void startClicked();

	// Behaviour when end game is clicked
    virtual void endClicked();

	// Behaviour when card is clicked
    virtual void cardClicked(int which);

	// Behaviour when switch from human/computer button is clicked
    virtual void switchClicked(int which);
protected:
	// Controller and model from MVC design pattern
    Controller *controller_;
    Model *model_;

	// Cache the 52 cards
    Gtk::Image* cards[52];

	// Cards in the hand
    Gtk::Image* hand_cards[13];
    
	// The Deck manager handles the images for all cards
	DeckGUI card_manager;

	// Graphics for the table of cards
    Gtk::Frame tableFrame;
	Gtk::Table table;

	// Graphics for the player's info: points/discards	
	Gtk::Frame playerFrame[4];
	Gtk::VBox player[4];
	Gtk::Label points[4];
	Gtk::Label discards[4];
	Gtk::HBox players;
 
	// Switch button from AI/Human
	Gtk::Button switchButton[4];

	// Set the seed, start game button and end game button
	Gtk::HBox header;
	Gtk::Button start_;
	Gtk::Button end_;
	Gtk::Entry seed_;

	// Display the cards in the hand
	Gtk::Frame handFrame_;
	Gtk::HBox hand_;	
    Gtk::Button handButtons_[13];	
	
	// VBox to contain the entire layout in the window
	Gtk::VBox layout;
};

#endif
