#include <cstdlib>
#include "Model.h"
#include "Game.h"

Model::Model() : seed(0), newGame(NULL) {
	for (int i = 0; i < numOfPlayers; i++) {
		isComputer_ = false;	
	} 
}

Model::~Model() {
	if (newGame != NULL) {
		delete newGame;
	}
}

void Model::startGame() {
	if (newGame != NULL) {
		delete newGame;
	}
	srand48(seed);
	newGame = new Game(isComputer_);
	
	while(!newGame->hasWon()) {
		newGame->newRound();
	}
	
	winners_ = newGame->winner();
	notify();	
}

void Model::endGame() {
	if (newGame != NULL) {
		delete newGame;
	}
	notify();
}

void Model::setSeed(const long seed) {
	seed_ = seed;
}

void Model::togglePlayerType(const int player) {
	isComputer_[player-1] ^= true;
	
	if (isComputer_[player-1] == true && newGame != NULL) {
		newGame->rageQuit(player);
		notify();
	}
}

bool Model::isPlayerComputer(const int player) {
	return isComputer_[player-1];
} 

std::vector<int> Model::getScores() {
	return newGame->scores();
}

std::vector<int> Model::getWinners() {
	return newGame->winner();
}
