#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Subject.h"
#include "Card.h"

class Game;

// Number of players (straights has 4 players)
const int numOfPlayers = 4;

class Model : public Subject {
public:
	// Constructor
	Model();

	// Destructor
	~Model();

	// Start/end the game
	void startGame();
	void endGame();

	// Set the RNG seed
	void setSeed(const long seed);

	// Toggle playing strategy of player: human/computer
	void togglePlayerType(const int player);

	// Determines whether a player is AI
	bool isPlayerComputer(const int player) const;

	// Accessor for updated scores of the game
	std::vector<int> getScores() const;

	// Accessor for the discards of every player
	std::vector<std::vector<Card> > getDiscards() const;

	// Determines who the starting player is
	int startingPlayer() const;

	// Determines whether the game has started or not
    bool gameStarted() const;

	// Determines who the current player is
    int currentPlayer() const;

	// Accessor for the cards on the table
    std::vector<Card> getTable() const;

	// Accessor for the current player's hand
    std::vector<Card> getCurHand() const;
    
	// Current player selects a card to play
	void selectCard(int); 

	// Display a message in the dialog box
	void setMessage(std::string msg);

	// Accessor for the message to display in the Dialog Box
    std::string getMessage() const;

	// Get the legal moves from the current player
    std::vector<int> getMoves() const;
	
private:
	// Game variables and flags
	int turn_;
    bool ended;

	// Which players are human/AI
	bool isComputer_[numOfPlayers];

	// Seed to start game
	long seed_;

	// Message to display in Dialog box
    std::string message_;

	// The game pointer
	Game *newGame;
};

#endif
