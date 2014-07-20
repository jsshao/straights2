#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Deck.h"
#include <fstream>

// Forward declaration
class Player;
class Model;

class Game {
public:
    // Constructor
    Game(bool *, Model *);

    // Destructor
    ~Game();

    // Start a new round of straights
    void newRound();

    // Called at the end of a round
    void endRound();

    // Human plays a card
	void play(Card c);

	// The AI plays a card
    void playAI();

	// Determine if game is over
    bool hasWon() const;

	// Helper function to determine the winner
    std::vector<int> winner() const;

	// Get the scores
	std::vector<int> scores() const;

	// Get the discards
	std::vector<std::vector<Card> > discards() const;

	// Choose the starting player (8S)
    int startingPlayer() const;

	// Gets the state of the current table
    std::vector<Card> getTable() const;

	// Gets the hand of a player
    std::vector<Card> getHand(int who) const;

	// Returns who the current player is
    int curPlayer() const;

	// Determins whether playing card C is legal
    bool isLegalMove(Card c) const;

	// Determines if player has a legal non-discarding move
    bool hasLegalMove() const;

	// Turns from Human to Computer
    void rageQuit();

private:
    // Deck ordering
    Deck deck_;

    // Cards on the table
    std::vector<Card> table_;

	// Legal moves
    int high[4];
    int low[4];
    int turns_;

    // Vector of players
    std::vector<Player*> players_;

	// Current player index
    int cur_player_;

	// Whether the players are computer or human
    bool is_computer[4];
    std::ofstream fs;
	
	// Model member to print dialog messages
	Model *model_;
};

#endif
