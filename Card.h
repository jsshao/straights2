#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>
#include <string>

// Enum type definitions for suit and rank of cards
enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
            EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
    // Allow extraction operator to modify private members
    friend std::istream &operator>>(std::istream &, Card &);

public:
    // Constructor
    Card(Suit, Rank);

    // Accessor for suit of the card
    Suit getSuit() const;

    // Accessor for rank of card as a string
    std::string getRankName() const;

    // Accessor for rank of the card
    Rank getRank() const;
    
private:
    // Private data members
    Suit suit_;
    Rank rank_;
};

// Overload equality operator
bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
