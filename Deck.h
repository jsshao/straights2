#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
    // Overload insertion operator to output deck
	friend std::ostream &operator<<(std::ostream &, const Deck &);
public:
    // Constructor
    Deck();

    // Shuffle the deck
    void shuffle();

    // Deal a single card
    Card deal();
private:
    // Data for the ordering of cards_
    std::vector<Card> cards_;

    // Keeps track of which card has been dealt
    int dealt_;

    // Disallows Copy constructor, assignment operator and equality operator
    Deck(Deck& copy);
    bool operator==(const Deck& other);
    void operator=(const Deck& other);
};

#endif
