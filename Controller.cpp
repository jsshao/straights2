#include "Controller.h"

Controller::Controller(Model *model) : model_(model) {}

Controller::~Controller() {}

void Controller::setSeed(const long seed) {
	model_->setSeed(seed);
}

void Controller::startGame() {
	model_->startGame();
}

void Controller::endGame() {
	model_->endGame();
}

void Controller::selectCard(int index) {
	model_->selectCard(index);
}

void Controller::togglePlayerType(int player) {
	model_->togglePlayerType(player);
}

