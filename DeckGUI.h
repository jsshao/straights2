#ifndef __DECK_GUI_H
#define __DECK_GUI_H
#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"
using std::vector;

// Deck GUI controls the card images of the deck

class DeckGUI {
public:
	// Constructor
	DeckGUI();

	// Destructor
	virtual ~DeckGUI();
	
	// Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getCard(Rank f, Suit s );   	

    // Returns the image to use for the placeholder.
	Glib::RefPtr<Gdk::Pixbuf> getNull();

private:
	// Contains the pixel buffer images
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   
}; 
#endif
