#include <cstdlib>
#include "Model.h"
#include "Game.h"
#include <iostream>
#include <sstream>
using namespace std;

// Constructor by initializing game variables
Model::Model() : turn_(0), seed_(0), message_(""), newGame(NULL) {
	for (int i = 0; i < numOfPlayers; i++) {
		isComputer_[i] = false;	
	} 
}

// Destructor that deletes the game pointer if in middle of a game
Model::~Model() {
	if (newGame != NULL) { 
        delete newGame;
	}
}

// Choose a card for the current player to play
void Model::selectCard(int index) {
    if (gameStarted() and (size_t)index < getCurHand().size()) {
        newGame->play(getCurHand()[index]);
        notify();
    }
}

// Begin the game by setting the seed and calling game constructor
void Model::startGame() {
	endGame();
    ended = false;
	srand48(seed_);
	newGame = new Game(isComputer_, this, seed_);
    turn_ = 1;
    if (ended) endGame();
	notify();	
}

// End the game by deleting game pointer and setting game variables to false
void Model::endGame() {
	if (newGame != NULL) {
		delete newGame;
        newGame = NULL;
	}
    ended = true;
    turn_ = 0;
	notify();
}

// Returns legal moves of current player
vector<int> Model::getMoves() const {
    vector<int> moves;
    vector<Card> hand = getCurHand();
    for (size_t i = 0; i < hand.size(); i++) {
        if (newGame->isLegalMove(hand[i])) {
            moves.push_back(i);
        }
    }
    return moves;
}

// Determines whether a game is in play
bool Model::gameStarted() const {
    return turn_ > 0;
}

// Mutator for the seed
void Model::setSeed(const long seed) {
	seed_ = seed;
}

// Toggle the player type from human to computer or vice-versa
void Model::togglePlayerType(const int player) {
	isComputer_[player-1] ^= true;
	
	if (gameStarted()) {
		newGame->rageQuit();
	}
    notify();
}

// Determines whether a player is AI
bool Model::isPlayerComputer(const int player) const {
	return isComputer_[player-1];
} 

// Returns scores of the round
std::vector<int> Model::getScores() const {
	if (newGame != NULL) {
		return newGame->scores();
	} else {
		vector<int> empty;
		return empty;
	} 
} 

// Returns the discarded cards of the round
std::vector<vector<Card> > Model::getDiscards() const {
	return newGame->discards();
}

// Returns who the starting player is
int Model::startingPlayer() const {
	return newGame->startingPlayer();
}

// Returns the current player
int Model::currentPlayer() const {
    return newGame->curPlayer();    
}

// Returns current state of the table
vector<Card> Model::getTable() const {
    return newGame->getTable();
}

// Returns current players hand
vector<Card> Model::getCurHand() const {
    return newGame->getHand(currentPlayer());
}

// Displays a message in a dialog box
void Model::setMessage(string msg) {
	message_ = msg;
	notify();
	message_ = "";
}

// Access the message to be displayed in dialog box
string Model::getMessage() const {
	return message_;
}
