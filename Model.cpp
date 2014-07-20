#include <cstdlib>
#include "Model.h"
#include "Game.h"
#include <iostream>
using namespace std;

Model::Model() : turn_(0), seed_(0), message_(""), newGame(NULL) {
	for (int i = 0; i < numOfPlayers; i++) {
		isComputer_[i] = false;	
	} 
}

Model::~Model() {
	if (newGame != NULL) { delete newGame;
	}
}

void Model::selectCard(int index) {
    newGame->play(getCurHand()[index]);
    notify();
}

void Model::startGame() {
	if (newGame != NULL) {
		delete newGame;
        newGame = NULL;
	}
	srand48(seed_);
	newGame = new Game(isComputer_);
	turn_ = 1;
	
	notify();	
}

void Model::endGame() {
	if (newGame != NULL) {
		delete newGame;
        newGame = NULL;
	}
    turn_ = 0;
	notify();
}

bool Model::gameStarted() const {
    return turn_ > 0;
}

void Model::setSeed(const long seed) {
	seed_ = seed;
}

void Model::togglePlayerType(const int player) {
	isComputer_[player-1] ^= true;
	
	if (isComputer_[player-1] == true && gameStarted()) {
		newGame->rageQuit(player);
	}
    notify();
}

bool Model::isPlayerComputer(const int player) const {
	return isComputer_[player-1];
} 

std::vector<int> Model::getScores() const {
	if (newGame != NULL) {
		return newGame->scores();
	} else {
		vector<int> empty;
		return empty;
	}
}

std::vector<vector<Card> > getDiscards() const {
	return newGame->discards();
}

std::vector<int> Model::getWinners() const {
	return newGame->winner();
}

int Model::startingPlayer() const {
	return newGame->startingPlayer();
}

int Model::currentPlayer() const {
    return newGame->curPlayer();    
}

vector<Card> Model::getTable() const {
    return newGame->getTable();
}

vector<Card> Model::getCurHand() const {
    return newGame->getHand(currentPlayer());
}

void Model::setMessage(string msg) {
	message_ = msg;
	notify();
	message_ = "";
}

string Model::getMessage() const {
	return message_;
}
