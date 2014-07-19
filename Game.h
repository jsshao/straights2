#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Deck.h"

// Forward declaration
class Player;

class Game {
public:
    // Constructor
    Game(bool *);

    // Destructor
    ~Game();

    // Start the game
    void start(); 

    // Start a new round of straights
    void newRound();

    // Print out the contents of the deck
    void printDeck() const;

	// Let a Player rageQuit
	void rageQuit(const int player);
	
	// Determine if game is over
    bool hasWon() const;

	// Helper function to determine the winner
    std::vector<int> winner() const;

	// Get the scores
	std::vector<int> scores() const;

	// Choose the starting player (8S)
    int startingPlayer() const;

private:
    // Deck ordering
    Deck deck_;

    // Cards on the table
    std::vector<Card> table_;

    // Vector of players
    std::vector<Player*> players_;
};

#endif
