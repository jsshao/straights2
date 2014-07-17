#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Deck.h"

// Constant for total number of cards
#define CARD_COUNT 52

using namespace std;

// Constructor
Deck::Deck() : dealt_(0) { 
    for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
        for (int rank = ACE; rank < RANK_COUNT; rank++) {
            cards_.push_back(Card((Suit) suit, (Rank) rank));
        }
    }
}

// Shuffle the deck using RNG
void Deck::shuffle() {
    int n = CARD_COUNT;

	while (n > 1) {
		int k = (int) (lrand48() % n);
		--n;
        swap(cards_[n], cards_[k]);
	}

    dealt_ = 0;
}

// Deal a single card while updating which card has been dealt
Card Deck::deal() {
    return cards_[dealt_++];
}

// Insertion operator to print out the 52 cards in the deck
ostream& operator<<(ostream& out, const Deck& deck) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            if (j) out << " ";
            out << deck.cards_[i*13+j];
        }
        out << endl;
    }
    return out;
}
