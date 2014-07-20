#include <cstdlib>
#include "Model.h"
#include "Game.h"

Model::Model() : turn(0), seed_(0), newGame(NULL) {
	for (int i = 0; i < numOfPlayers; i++) {
		isComputer_[i] = false;	
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
	srand48(seed_);
	newGame = new Game(isComputer_);
	turn = 1;
	
	while(!newGame->hasWon()) {
		// NEEDS WORK
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

int Model::startingPlayer() {
	return newGame->startingPlayer();
}
