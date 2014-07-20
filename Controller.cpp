#include "Controller.h"

// Initialize model in constructor
Controller::Controller(Model *model) : model_(model) {}

// Destructor has no behaviour as constructor does not dyn allocate the model
Controller::~Controller() {}

// Set the seed
void Controller::setSeed(const long seed) {
	model_->setSeed(seed);
}

// Tells model to start game
void Controller::startGame() {
	model_->startGame();
}

// Tells model to end game
void Controller::endGame() {
	model_->endGame();
}

// Tells model to play the card that is "index" from the left
void Controller::selectCard(int index) {
	model_->selectCard(index);
}

// Switch between computer and human
void Controller::togglePlayerType(int player) {
	model_->togglePlayerType(player);
}

